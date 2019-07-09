/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SkinningData.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpeck <dpeck@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/06 16:59:38 by dpeck             #+#    #+#             */
/*   Updated: 2019/07/06 17:00:41 by dpeck            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "SkinningData.hpp"

SkinningData::SkinningData(std::vector<std::string jointOrder, std::vector<VertexSkinData> verticesSkinData) :
    _jointOrder(jointOrder), _verticesSkinData(verticesSkinData)
{

}