/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ColladaLoader.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpeck <dpeck@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/07 16:36:22 by dpeck             #+#    #+#             */
/*   Updated: 2019/07/08 19:31:32 by dpeck            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ColladaLoader.hpp"
#include <iostream>

AnimatedModelData ColladaLoader::loadColladaModel(std::string colladaFile, int maxWeights)
{
    pugi::xml_document doc;
    pugi::xml_parse_result result = doc.load_file(colladaFile.c_str());

    std::cout << "Load result: " << result.description() << std::endl;

    SkinLoader skinLoader(doc.child("library_controllers"), maxWeights);
    SkinningData skinningData = skinLoader.extractSkinData();

    SkeletonLoader jointsLoader(doc.child("library_visual_scenes"), skinningData._jointOrder);
    SkeletonData jointsData = jointsLoader.extractBoneData();

    GeometryLoader g(doc.child("library_geometries"), skinningData._verticesSkinData);
    MeshData meshData = g.extractModelData();

    return AnimatedModelData(meshData, jointsData);
}

AnimationData ColladaLoader::loadColladaAnimation(std::string colladaFile)
{
    pugi::xml_document doc;
    pugi::xml_parse_result result = doc.load_file(colladaFile.c_str());

    pugi::xml_node animNode = doc.child("library_animations");
    pugi::xml_node jointsNode = doc.child("library_visual_scenes");
    AnimationLoader loader(animNode, jointsNode);
    AnimationData animData = loader.extractAnimation();
    return animData;
}