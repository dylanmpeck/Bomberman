/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AnimationLoader.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpeck <dpeck@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/07 12:00:55 by dpeck             #+#    #+#             */
/*   Updated: 2019/07/08 17:41:34 by dpeck            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "AnimationLoader.hpp"
#include "vendor/glm/gtc/type_ptr.hpp"
#include "pugixml/src/pugixml.hpp"

glm::mat4 AnimationLoader::CORRECTION = glm::rotate(glm::mat4(1.0f), glm::radians(-90.0f), glm::vec3(1.0, 0.0, 0.0));

AnimationLoader::AnimationLoader(XmlNode * animationData, XmlNode * jointHierarchy)
{
    this->_animationData = animationData;
    this->_jointHierarchy = jointHierarchy;
}

AnimationData AnimationLoader::extractAnimation()
{
    std::string rootNode = findRootJointName();
    std::vector<float> times = getKeyTimes();
    float duration = times.back();
    std::vector<KeyFrameData> keyFrames = initKeyFrames(times);
    std::vector<XmlNode *> animationNodes = _animationData->getChildren("animation");
    for (XmlNode * jointNode : animationNodes)
        loadJointTransforms(keyFrames, jointNode, rootNode);
    return (AnimationData(duration, keyFrames));
}

//might want to make sure this is working correctly
std::vector<float> AnimationLoader::getKeyTimes()
{
    XmlNode * timeData = _animationData->getChild("animation")->getChild("source")->getChild("float_array");
    std::string timeStr = timeData->getData();
    std::vector<std::string> rawTimes;
    size_t pos = 0;
    while ((pos = timeStr.find(" ")) != std::string::npos)
    {
        rawTimes.push_back(timeStr.substr(0, pos));
        timeStr.erase(0, pos + 1);
    }
    std::vector<float> times(rawTimes.size(), 0.0f);
    for (unsigned int i = 0; i < times.size(); i++)
        times[i] = stof(rawTimes[i]);
    return (times);
}

std::vector<KeyFrameData> AnimationLoader::initKeyFrames(std::vector<float> times)
{
    std::vector<KeyFrameData> frames;
    for (unsigned int i = 0; i < times.size(); i++)
        frames.push_back(KeyFrameData(times[i]));
    return (frames);
}

void AnimationLoader::loadJointTransforms(std::vector<KeyFrameData> frames, XmlNode * jointData, std::string rootNodeID)
{
    std::string jointNameID = getJointName(jointData);
    std::string dataID = getDataID(jointData);
    XmlNode * transformData = jointData->getChildWithAttributes("source", "id", dataID);

    std::string transformDataChildStr = transformData->getChild("float_array")->getData();
    std::vector<std::string> rawData;
    size_t pos = 0;
    while ((pos = transformDataChildStr.find(" ")) != std::string::npos)
    {
        rawData.push_back(transformDataChildStr.substr(0, pos));
        transformDataChildStr.erase(0, pos + 1);
    }

    processTransforms(jointNameID, rawData, frames, jointNameID == rootNodeID);
}

std::string AnimationLoader::getDataID(XmlNode * jointData)
{
    XmlNode * node = jointData->getChild("sampler")->getChildWithAttributes("input", "semantic", "OUTPUT");
    return (node->getAttribute("source").substr(1));
}

std::string AnimationLoader::getJointName(XmlNode * jointData)
{
    XmlNode * channelNode = jointData->getChild("channel");
    std::string data = channelNode->getAttribute("target");
    size_t pos = data.find("/");
    std::string name = data.substr(0, pos);
    return (name);
}

void AnimationLoader::processTransforms(std::string jointName, std::vector<std::string> rawData, std::vector<KeyFrameData> & keyFrames, bool root)
{
    float matrixData[16];
    for (unsigned int i = 0; i < keyFrames.size(); i++)
    {
        for (int j = 0; j < 16; j++)
            matrixData[j] = stof(rawData[i * 16 + j]);
        glm::mat4 transform = glm::make_mat4(matrixData);
        transform = glm::transpose(transform);
        if (root)
            transform = CORRECTION * transform;
        keyFrames[i].addJointTransform(JointTransformData(jointName, transform));
    }
}

std::string AnimationLoader::findRootJointName()
{
    XmlNode * skeleton = _jointHierarchy->getChild("visual_scene")->getChildWithAttributes("node", "id", "Armature");
    return skeleton->getChild("node")->getAttribute("id");
}