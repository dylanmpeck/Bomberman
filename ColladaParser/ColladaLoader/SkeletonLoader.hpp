/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SkeletonLoader.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpeck <dpeck@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/07 19:53:30 by dpeck             #+#    #+#             */
/*   Updated: 2019/07/08 19:45:41 by dpeck            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SKELETONLOADER_HPP
#define SKELETONLOADER_HPP

#include <vector>
#include "vendor/glm/glm.hpp"
#include "vendor/glm/gtc/matrix_transform.hpp"
#include "pugixml/src/pugixml.hpp"
#include "DataStructures/SkeletonData.hpp"
#include "DataStructures/JointData.hpp"

class SkeletonLoader {

private:
    static glm::mat4 CORRECTION;

    pugi::xml_node _armatureData;
    std::vector<std::string> _boneOrder;
    int _jointCount;

public:
    SkeletonLoader(pugi::xml_node visualSceneNode, std::vector<std::string> boneOrder);
    SkeletonData extractBoneData();

private:
    JointData loadJointData(pugi::xml_node jointNode, bool isRoot);
    JointData extractMainJointData(pugi::xml_node jointNode, bool isRoot);
    std::vector<float> convertData(std::vector<std::string> rawData);
};

#endif