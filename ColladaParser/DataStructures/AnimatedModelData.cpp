/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AnimatedModelData.cpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpeck <dpeck@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/06 15:28:20 by dpeck             #+#    #+#             */
/*   Updated: 2019/07/06 15:29:34 by dpeck            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "AnimatedModelData.hpp"

AnimatedModelData::AnimatedModelData(MeshData mesh, SkeletonData joints) :
    _joints(joints), _mesh(mesh)
{

}

SkeletonData AnimatedModelData::getJointsData()
{
    return (_joints);
}

MeshData AnimatedModelData::getMeshData()
{
    return (_mesh);
}