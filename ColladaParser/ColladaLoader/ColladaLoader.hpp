/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ColladaLoader.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpeck <dpeck@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/07 16:28:27 by dpeck             #+#    #+#             */
/*   Updated: 2019/07/07 16:35:54 by dpeck            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COLLADALOADER_HPP
#define COLLADALOADER_HPP

#include <fstream>
#include "DataStructures/AnimatedModelData.hpp"
#include "DataStructures/AnimationData.hpp"
#include "DataStructures/MeshData.hpp"
#include "DataStructures/SkinningData.hpp"
#include "DataStructures/SkeletonData.hpp"
#include "xmlParser/XmlNode.hpp"
#include "AnimationLoader.hpp"

class ColladaLoader {

public:
    static AnimatedModelData loadColladaModel(std::ifstream colladaFile, int maxWeights);
    static AnimationData loadColladaAnimation(std::ifstream colladaFile);
};

#endif