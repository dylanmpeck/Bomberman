/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AnimatedModelData.hpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpeck <dpeck@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/06 15:27:05 by dpeck             #+#    #+#             */
/*   Updated: 2019/07/06 18:02:35 by dpeck            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ANIMATEDMODELDATA_HPP
#define ANIMATEDMODELDATA_HPP

#include "SkeletonData.hpp"
#include "MeshData.hpp"

class AnimatedModelData {

private:
    SkeletonData _joints;
    MeshData _mesh;

public:
    AnimatedModelData(MeshData mesh, SkeletonData joints);
    SkeletonData getJointsData();
    MeshData getMeshData();

};

#endif