/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AnimatedModelLoader.cpp                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpeck <dpeck@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/09 14:15:48 by dpeck             #+#    #+#             */
/*   Updated: 2019/07/12 17:41:58 by dpeck            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "AnimatedModelLoader.hpp"
#include "ColladaParser/DataStructures/AnimatedModelData.hpp"
#include "ColladaParser/ColladaLoader/ColladaLoader.hpp"
#include <iostream>

AnimatedModel * AnimatedModelLoader::loadEntity(std::string modelFile, std::string textureFile)
{
    //std::cout << "0" << std::endl;
    AnimatedModelData entityData = ColladaLoader::loadColladaModel(modelFile, 3); // 3 = MAX_WEIGHTS. Should set this as variable somewhere
   // std::cout << "1" << std::endl;
    VertexArray * model = createVAO(entityData.getMeshData());
    //std::cout << "2" << std::endl;
    TextureLoader * texture = &ResourceManager::loadTexture(textureFile, "animatedModel");
    //std::cout << "3" << std::endl;
    SkeletonData skeletonData = entityData.getJointsData();
    //std::cout << "4" << std::endl;
    Joint headJoint = createJoints(skeletonData._headJoint);
    //std::cout << "5" << std::endl;
    return new AnimatedModel(model, texture, headJoint, skeletonData._jointCount);
}

Joint AnimatedModelLoader::createJoints(JointData data)
{
    Joint joint(data._index, data._nameID, data._bindLocalTransform);
    for (JointData child : data._children)
        joint.addChild(createJoints(child));
    return (joint);
}

VertexArray * AnimatedModelLoader::createVAO(MeshData data)
{
    VertexArray * vao = new VertexArray();
    vao->bind();
    vao->createIndexBuffer(data.getIndices());
    vao->createAttribute(0, data.getVertices(), 3);
    vao->createAttribute(1, data.getTextureCoords(), 2);
    vao->createAttribute(2, data.getNormals(), 3);
    vao->createIntAttribute(3, data.getJointIDs(), 3);
    vao->createAttribute(4, data.getVertexWeights(), 3);
    return (vao);
}