/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SkinLoader.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpeck <dpeck@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/07 20:29:46 by dpeck             #+#    #+#             */
/*   Updated: 2019/07/11 15:57:04 by dpeck            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "SkinLoader.hpp"
#include <iostream>

SkinLoader::SkinLoader(pugi::xml_node controllersNode, int maxWeights)
{
    this->_skinningData = controllersNode.child("controller").child("skin");
    this->_maxWeights = maxWeights;
}

SkinningData * SkinLoader::extractSkinData()
{
    std::vector<std::string> jointList = loadJointsList();
    std::vector<float> weights = loadWeights();
    pugi::xml_node weightsDataNode = _skinningData.child("vertex_weights");
    std::vector<int> effectorJointCounts = getEffectiveJointsCounts(weightsDataNode);
    std::vector<VertexSkinData *> vertexWeights = getSkinData(weightsDataNode, effectorJointCounts, weights);
    return (new SkinningData(jointList, vertexWeights));
}

std::vector<std::string> SkinLoader::loadJointsList()
{
    pugi::xml_node inputNode = _skinningData.child("vertex_weights");
    std::string jointDataID = inputNode.find_child_by_attribute("input", "semantic", "JOINT").attribute("source").value();
    jointDataID = jointDataID.substr(1);
    pugi::xml_node jointsNode = _skinningData.find_child_by_attribute("source", "id", jointDataID.c_str()).child("Name_array");

    std::string jointsDataStr = jointsNode.child_value();
    std::vector<std::string> jointsList;
    size_t pos = 0;
    while ((pos = jointsDataStr.find(" ")) != std::string::npos)
    {
        jointsList.push_back(jointsDataStr.substr(0, pos));
        jointsDataStr.erase(0, pos + 1);
    }
    jointsList.push_back(jointsDataStr.substr(0, pos));
    std::cout << "joints data: " << jointsList.back() << std::endl;

    return (jointsList);
}

std::vector<float> SkinLoader::loadWeights()
{
    pugi::xml_node inputNode = _skinningData.child("vertex_weights");
    std::string weightsDataID = inputNode.find_child_by_attribute("input", "semantic", "WEIGHT").attribute("source").value();
    weightsDataID = weightsDataID.substr(1);
    pugi::xml_node weightsNode = _skinningData.find_child_by_attribute("source", "id", weightsDataID.c_str()).child("float_array");
    
    std::string weightsDataStr = weightsNode.child_value();
    std::vector<std::string> rawData;
    size_t pos = 0;
    while ((pos = weightsDataStr.find(" ")) != std::string::npos)
    {
        rawData.push_back(weightsDataStr.substr(0, pos));
        weightsDataStr.erase(0, pos + 1);
    }
    rawData.push_back(weightsDataStr.substr(0, pos));
    std::cout << "weights data: " << rawData.back() << std::endl;

    std::vector<float> weights;
    for (unsigned int i = 0; i < rawData.size(); i++)
        weights.push_back(std::stof(rawData[i]));
    return (weights);
}

std::vector<int> SkinLoader::getEffectiveJointsCounts(pugi::xml_node weightsDataNode)
{
    std::string rawDataStr = weightsDataNode.child("vcount").child_value();
    //std::cout << rawDataStr << std::endl;
    std::vector<std::string> rawData;
    size_t pos = 0;
    while ((pos = rawDataStr.find(" ")) != std::string::npos)
    {
        rawData.push_back(rawDataStr.substr(0, pos));
        rawDataStr.erase(0, pos + 1);
    }
    //rawData.push_back(rawDataStr.substr(0, pos));
    std::cout << "effective joints data: " << rawData.back() << std::endl;

    //std::cout << std::endl;

    //for (std::string num : rawData)
     //   std::cout << num << " ";

    //std::cout << std::endl;

    std::vector<int> counts;
    for (unsigned int i = 0; i < rawData.size(); i++)
        counts.push_back(std::stoi(rawData[i]));

    //std::cout << std::endl;
    //for (int num : counts)
    //    std::cout << num << " ";
    //std::cout << std::endl;
    return (counts);
}

std::vector<VertexSkinData *> SkinLoader::getSkinData(pugi::xml_node weightsDataNode, std::vector<int> counts, std::vector<float> weights)
{
    std::string rawDataStr = weightsDataNode.child("v").child_value();
    std::vector<std::string> rawData;
    size_t pos = 0;
    while ((pos = rawDataStr.find(" ")) != std::string::npos)
    {
        rawData.push_back(rawDataStr.substr(0, pos));
        rawDataStr.erase(0, pos + 1);
    }
    rawData.push_back(rawDataStr.substr(0, pos));
    std::cout << "skin data: " << rawData.back() << std::endl;

    std::vector<VertexSkinData *> skinningData;
    int pointer = 0;
    for (int count : counts)
    {
        VertexSkinData * skinData = new VertexSkinData();
        for (int i = 0; i < count; i++)
        {
            int jointID = std::stoi(rawData[pointer++]);
            int weightID = std::stoi(rawData[pointer++]);
            skinData->addJointEffect(jointID, weights[weightID]);
        }
        skinData->limitJointNumber(_maxWeights);
        skinningData.push_back(skinData);
    }
    return (skinningData);
}