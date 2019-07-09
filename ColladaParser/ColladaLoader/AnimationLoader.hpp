/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AnimationLoader.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpeck <dpeck@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/06 15:17:42 by dpeck             #+#    #+#             */
/*   Updated: 2019/07/08 19:21:29 by dpeck            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ANIMATIONLOADER_HPP
#define ANIMATIONLOADER_HPP

#include <vector>
#include "vendor/glm/glm.hpp"
#include "vendor/glm/gtc/matrix_transform.hpp"
#include "pugixml/src/pugixml.hpp"

#include "DataStructures/AnimationData.hpp"
#include "DataStructures/KeyFrameData.hpp"

class AnimationLoader {

private:
    static glm::mat4 CORRECTION;
    pugi::xml_node _animationData;
    pugi::xml_node _jointHierarchy;

public:
    AnimationLoader(pugi::xml_node animationData, pugi::xml_node jointHierarchy);
    AnimationData extractAnimation();

private:
    std::vector<float> getKeyTimes();
    std::vector<KeyFrameData> initKeyFrames(std::vector<float> times);
    void loadJointTransforms(std::vector<KeyFrameData> frames, pugi::xml_node jointData, std::string rootNodeId);
    std::string getDataID(pugi::xml_node jointData);
    std::string getJointName(pugi::xml_node jointData);
    void processTransforms(std::string jointName, std::vector<std::string> rawData, std::vector<KeyFrameData> & keyFrames, bool root);
    std::string findRootJointName();
};

#endif