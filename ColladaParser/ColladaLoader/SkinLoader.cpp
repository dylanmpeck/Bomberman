/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SkinLoader.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpeck <dpeck@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/07 20:29:46 by dpeck             #+#    #+#             */
/*   Updated: 2019/07/07 20:50:45 by dpeck            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "SkinLoader.hpp"

SkinLoader::SkinLoader(XmlNode * controllersNode, int maxWeights)
{
    this->_skinningData = controllersNode->getChild("controller")->getChild("skin");
    this->_maxWeights = maxWeights;
}

SkinningData SkinLoader::extractSkinData()
{
    std::vector<std::string> jointList = loadJointsList();
    std::vector<float> weights = loadWeights();
    XmlNode * weightsDataNode = _skinningData->getChild("vertex_weights");
    std::vector<int> effectorJointCounts = getEffectiveJointsCounts(weightsDataNode);
    std::vector<VertexSkinData> vertexWeights = getSkinData(weightsDataNode, effectorJointCounts, weights);
    return (SkinningData(jointList, vertexWeights));
}

std::vector<std::string> SkinLoader::loadJointsList()
{
    XmlNode * inputNode = _skinningData->getChild("vertex_weights");
    std::string jointDataID = inputNode->getChildWithAttributes("input", "semantic", "JOINT")->getAttribute("source").substr(1);
    XmlNode * jointsNode = _skinningData->getChildWithAttributes("source", "id", jointDataID)->getChild("Name_array");

    std::string jointsDataStr = jointsNode->getData();
    std::vector<std::string> jointsList;
    size_t pos = 0;
    while ((pos = jointsDataStr.find(" ")) != std::string::npos)
    {
        jointsList.push_back(jointsDataStr.substr(0, pos));
        jointsDataStr.erase(0, pos + 1);
    }

    return (jointsList);
}

std::vector<float> SkinLoader::loadWeights()
{
    XmlNode * inputNode = _skinningData->getChild("vertex_weights");
    std::string weightsDataID = inputNode->getChildWithAttributes("input", "semantic", "WEIGHT")->getAttribute("source").substr(1);
    XmlNode * weightsNode = _skinningData->getChildWithAttributes("source", "id", weightsDataID)->getChild("float_array");
    
    std::string weightsDataStr = weightsNode->getData();
    std::vector<std::string> rawData;
    size_t pos = 0;
    while ((pos = weightsDataStr.find(" ")) != std::string::npos)
    {
        rawData.push_back(weightsDataStr.substr(0, pos));
        weightsDataStr.erase(0, pos + 1);
    }

    std::vector<float> weights;
    for (unsigned int i = 0; i < rawData.size(); i++)
        weights.push_back(std::stof(rawData[i]));
    return (weights);
}

std::vector<int> SkinLoader::getEffectiveJointsCounts(XmlNode * weightsDataNode)
{
    std::string rawDataStr = weightsDataNode->getChild("vcount")->getData();
    std::vector<std::string> rawData;
    size_t pos = 0;
    while ((pos = rawDataStr.find(" ")) != std::string::npos)
    {
        rawData.push_back(rawDataStr.substr(0, pos));
        rawDataStr.erase(0, pos + 1);
    }

    std::vector<int> counts;
    for (unsigned int i = 0; i < rawData.size(); i++)
        counts.push_back(std::stoi(rawData[i]));
    return (counts);
}

std::vector<VertexSkinData> SkinLoader::getSkinData(XmlNode * weightsDataNode, std::vector<int> counts, std::vector<float> weights)
{
    std::string rawDataStr = weightsDataNode->getChild("v")->getData();
    std::vector<std::string> rawData;
    size_t pos = 0;
    while ((pos = rawDataStr.find(" ")) != std::string::npos)
    {
        rawData.push_back(rawDataStr.substr(0, pos));
        rawDataStr.erase(0, pos + 1);
    }

    std::vector<VertexSkinData> skinningData;
    int pointer = 0;
    for (int count : counts)
    {
        VertexSkinData skinData;
        for (int i = 0; i < count; i++)
        {
            int jointID = std::stoi(rawData[pointer++]);
            int weightID = std::stoi(rawData[pointer++]);
            skinData.addJointEffect(jointID, weights[weightID]);
        }
        skinData.limitJointNumber(_maxWeights);
        skinningData.push_back(skinData);
    }
    return (skinningData);
}