/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ColladaLoader.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpeck <dpeck@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/07 16:36:22 by dpeck             #+#    #+#             */
/*   Updated: 2019/07/10 18:56:23 by dpeck            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ColladaLoader.hpp"
#include <iostream>

AnimatedModelData ColladaLoader::loadColladaModel(std::string colladaFile, int maxWeights)
{
    pugi::xml_document doc;
    pugi::xml_parse_result result = doc.load_file(colladaFile.c_str(), pugi::parse_default|pugi::parse_declaration);

    std::cout << "Load result: " << result.description() << std::endl;

    pugi::xml_node root = doc.document_element();

    SkinLoader skinLoader(root.child("library_controllers"), maxWeights);
    SkinningData * skinningData = skinLoader.extractSkinData();

    SkeletonLoader jointsLoader(root.child("library_visual_scenes"), skinningData->_jointOrder);
    SkeletonData jointsData = jointsLoader.extractBoneData();

    GeometryLoader g(root.child("library_geometries"), skinningData->_verticesSkinData);
    MeshData meshData = g.extractModelData();

    delete skinningData;
    return AnimatedModelData(meshData, jointsData);
}

AnimationData ColladaLoader::loadColladaAnimation(std::string colladaFile)
{
    pugi::xml_document doc;
    pugi::xml_parse_result result = doc.load_file(colladaFile.c_str(), pugi::parse_default|pugi::parse_declaration);

    std::cout << "Load result: " << result.description() << std::endl;

    pugi::xml_node root = doc.document_element();

    pugi::xml_node animNode = root.child("library_animations");
    pugi::xml_node jointsNode = root.child("library_visual_scenes");
    AnimationLoader loader(animNode, jointsNode);
    AnimationData animData = loader.extractAnimation();
    return animData;
}