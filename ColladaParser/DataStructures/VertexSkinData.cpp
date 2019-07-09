/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   VertexSkinData.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpeck <dpeck@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/06 17:39:39 by dpeck             #+#    #+#             */
/*   Updated: 2019/07/06 18:00:46 by dpeck            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "VertexSkinData.hpp"
#include <algorithm>

void VertexSkinData::addJointEffect(int jointID, float weight)
{
    std::vector<int>::iterator jointIt = _jointIDs.begin();
    std::vector<float>::iterator weightsIt = _weights.begin();
    for (unsigned int i = 0; i < _weights.size(); i++)
    {
        if (weight > _weights[i])
        {
            _jointIDs.insert(jointIt + i, jointID);
            _weights.insert(weightsIt + i, weight);
            return;
        }
    }
    _jointIDs.push_back(jointID);
    _weights.push_back(weight);
}

void VertexSkinData::limitJointNumber(int max)
{
    if (_jointIDs.size() > max)
    {
        std::vector<float> topWeights(max, 0.0f);
        float total = saveTopWeights(topWeights);
        refillWeightList(topWeights, total);
        removeExcessJointIDs(max);
    }
    else if (_jointIDs.size() < max)
        fillEmptyWeights(max);
}

float VertexSkinData::saveTopWeights(std::vector<float> topWeightsVector)
{
    float total = 0;
    for (unsigned int i = 0; i < topWeightsVector.size(); i++)
    {
        topWeightsVector[i] = _weights[i];
        total += topWeightsVector[i];
    }
    return (total);
}

void VertexSkinData::refillWeightList(std::vector<float> topWeights, float total)
{
    _weights.clear();
    for (unsigned int i = 0; i < topWeights.size(); i++)
        _weights.push_back(std::min(topWeights[i] / total, 1.0f));
}

void VertexSkinData::removeExcessJointIDs(int max)
{
    while (_jointIDs.size() > max)
        _jointIDs.pop_back();
}