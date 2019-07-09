/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ColladaLoader.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpeck <dpeck@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/07 16:36:22 by dpeck             #+#    #+#             */
/*   Updated: 2019/07/07 16:43:44 by dpeck            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ColladaLoader.hpp"

AnimatedModelData ColladaLoader::loadColladaModel(std::ifstream colladaFile, int maxWeights)
{
    XmlNode * node = XmlParser::loadXmlFile(colladaFile);

    SkinLoader skinLoader(node->getChild("library_controllers"), maxWeights);
    SkinningData skinningData = skinLoader.extractSkinData();

    SkeletonLoader jointsLoader(node->getChild("library_visual_scenes"), skinningData._jointOrder);
    SkeletonData jointsData = jointsLoader.extractBoneData();

    GeometryLoader g(node->getChild("library_geometries"), skinningData._verticesSkinData);
    MeshData meshData = g.extractModelData();

    return AnimatedModelData(meshData, jointsData);
}

AnimationData ColladaLoader::loadColladaAnimation(std::ifstream colladaFile)
{
    XmlNode * node = XmlParser::loadXmlFile(colladaFile);
    XmlNode * animNode = node->getChild("library_animations");
    XmlNode * jointsNode = node->getChild("library_visual_scenes");
    AnimationLoader loader(animNode, jointsNode);
    AnimationData animData = loader.extractAnimation();
    return animData;
}