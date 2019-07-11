/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AnimatedModelLoader.hpp                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpeck <dpeck@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/08 20:21:48 by dpeck             #+#    #+#             */
/*   Updated: 2019/07/10 19:44:10 by dpeck            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ANIMATEDMODELLOADER_HPP
#define ANIMATEDMODELLOADER_HPP

#include <string>
#include "AnimatedModel.hpp"
#include "ResourceManager.hpp"
#include "ColladaParser/DataStructures/JointData.hpp"
#include "ColladaParser/DataStructures/MeshData.hpp"

class AnimatedModelLoader {

public:
    static AnimatedModel * loadEntity(std::string modelFile, std::string textureFile);
    static Joint createJoints(JointData data);
    static VertexArray * createVAO(MeshData data);
};

#endif