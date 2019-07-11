/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AnimationLoader.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpeck <dpeck@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/07 12:00:55 by dpeck             #+#    #+#             */
/*   Updated: 2019/07/11 15:51:09 by dpeck            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "AnimationLoader.hpp"
#include <iostream>
#include "vendor/glm/gtc/type_ptr.hpp"


glm::mat4 AnimationLoader::CORRECTION = glm::rotate(glm::mat4(1.0f), glm::radians(-90.0f), glm::vec3(1.0, 0.0, 0.0));

AnimationLoader::AnimationLoader(pugi::xml_node animationData, pugi::xml_node jointHierarchy)
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
    std::vector<pugi::xml_node> animationNodes;
    for (pugi::xml_node child : _animationData.children("animation"))
        animationNodes.push_back(child);
    for (pugi::xml_node jointNode : animationNodes)
        loadJointTransforms(keyFrames, jointNode, rootNode);
    return (AnimationData(duration, keyFrames));
}

//might want to make sure this is working correctly
std::vector<float> AnimationLoader::getKeyTimes()
{
    pugi::xml_node timeData = _animationData.child("animation").child("source").child("float_array");
    std::string timeStr = timeData.child_value();
    std::vector<std::string> rawTimes;
    size_t pos = 0;
    while ((pos = timeStr.find(" ")) != std::string::npos)
    {
        rawTimes.push_back(timeStr.substr(0, pos));
        timeStr.erase(0, pos + 1);
    }
    rawTimes.push_back(timeStr.substr(0, pos));
    std::cout << "TimeStr: " << rawTimes.back() << std::endl;
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

void AnimationLoader::loadJointTransforms(std::vector<KeyFrameData> frames, pugi::xml_node jointData, std::string rootNodeID)
{
    std::string jointNameID = getJointName(jointData);
    std::string dataID = getDataID(jointData);
    pugi::xml_node transformData = jointData.find_child_by_attribute("source", "id", dataID.c_str());

    std::string transformDataChildStr = transformData.child("float_array").child_value();
    std::vector<std::string> rawData;
    size_t pos = 0;
    while ((pos = transformDataChildStr.find(" ")) != std::string::npos)
    {
        rawData.push_back(transformDataChildStr.substr(0, pos));
        transformDataChildStr.erase(0, pos + 1);
    }
    rawData.push_back(transformDataChildStr.substr(0, pos));
    std::cout << "transformDataChildStr: " << rawData.back() << std::endl;

    processTransforms(jointNameID, rawData, frames, jointNameID == rootNodeID);
}

std::string AnimationLoader::getDataID(pugi::xml_node jointData)
{
    pugi::xml_node node = jointData.child("sampler").find_child_by_attribute("input", "semantic", "OUTPUT");
    pugi::xml_attribute attr = node.attribute("source");
    std::string attrStr = attr.value();
    return (attrStr.substr(1));
}

std::string AnimationLoader::getJointName(pugi::xml_node jointData)
{
    pugi::xml_node channelNode = jointData.child("channel");
    std::string data = channelNode.attribute("target").value();
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
    pugi::xml_node skeleton = _jointHierarchy.child("visual_scene").find_child_by_attribute("node", "id", "Armature");
    return skeleton.child("node").attribute("id").value();
}