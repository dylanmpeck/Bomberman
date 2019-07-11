/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SkinningData.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpeck <dpeck@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/06 16:59:38 by dpeck             #+#    #+#             */
/*   Updated: 2019/07/10 16:41:17 by dpeck            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "SkinningData.hpp"

SkinningData::SkinningData()
{
    
}

SkinningData::~SkinningData()
{
    //for (VertexSkinData * skinData : this->_verticesSkinData)
    //    delete skinData;
}

SkinningData::SkinningData(std::vector<std::string> jointOrder, std::vector<VertexSkinData *> verticesSkinData)
{
    this->_jointOrder.reserve(jointOrder.size());
    for (std::string joint : jointOrder)
        this->_jointOrder.push_back(joint);

    this->_verticesSkinData.reserve(verticesSkinData.size());
    for (VertexSkinData * skinData : verticesSkinData)
        this->_verticesSkinData.push_back(skinData);
}