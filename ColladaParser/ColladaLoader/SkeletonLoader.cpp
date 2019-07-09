/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SkeletonLoader.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpeck <dpeck@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/07 20:00:54 by dpeck             #+#    #+#             */
/*   Updated: 2019/07/07 20:25:03 by dpeck            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "SkeletonLoader.hpp"
#include "vendor/glm/gtc/type_ptr.hpp"

glm::mat4 SkeletonLoader::CORRECTION = glm::rotate(glm::mat4(1.0f), glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f));

SkeletonLoader::SkeletonLoader(XmlNode * visualSceneNode, std::vector<std::string> boneOrder)
{
    this->_jointCount = 0;
    this->_armatureData = visualSceneNode->getChild("visual_scene")->getChildWithAttributes("node", "id", "Armature");
    this->_boneOrder = boneOrder;
}

SkeletonData SkeletonLoader::extractBoneData()
{
    XmlNode * headNode = _armatureData->getChild("node");
    JointData headJoint = loadJointData(headNode, true);
    return SkeletonData(_jointCount, headJoint);
}

JointData SkeletonLoader::loadJointData(XmlNode * jointNode, bool isRoot)
{
    JointData joint = extractMainJointData(jointNode, isRoot);
    for (XmlNode * childNode : jointNode->getChildren("node"))
        joint.addChild(loadJointData(childNode, false));
    return (joint);
}

JointData SkeletonLoader::extractMainJointData(XmlNode * jointNode, bool isRoot)
{
    std::string nameID = jointNode->getAttribute("id");
    int index = 0;
    for (std::string bone : _boneOrder)
    {
        if (bone == nameID)
            break;
        index++;
    }

    std::string matrixDataStr = jointNode->getChild("matrix")->getData();
    std::vector<std::string> matrixData;
    size_t pos = 0;
    while ((pos = matrixDataStr.find(" ")) != std::string::npos)
    {
        matrixData.push_back(matrixDataStr.substr(0, pos));
        matrixDataStr.erase(0, pos + 1);
    }

    glm::mat4 matrix(1.0f);
    matrix = glm::make_mat4(&convertData(matrixData)[0]);
    matrix = glm::transpose(matrix);
    if (isRoot)
        matrix = CORRECTION * matrix;
    _jointCount++;

    return JointData(index, nameID, matrix);
}

std::vector<float> SkeletonLoader::convertData(std::vector<std::string> rawData)
{
    std::vector<float> matrixData;
    for (unsigned int i = 0; i < rawData.size(); i++)
        matrixData[i] = std::stof(rawData[i]);
    return (matrixData);
}