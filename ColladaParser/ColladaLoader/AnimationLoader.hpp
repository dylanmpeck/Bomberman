/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AnimationLoader.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpeck <dpeck@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/06 15:17:42 by dpeck             #+#    #+#             */
/*   Updated: 2019/07/08 17:41:46 by dpeck            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ANIMATIONLOADER_HPP
#define ANIMATIONLOADER_HPP

#include <vector>
#include "vendor/glm/glm.hpp"
#include "vendor/glm/gtc/matrix_transform.hpp"
#include "pugixml/src/pugixml.hpp"

#include "DataStructures/AnimationData.hpp"
#include "xmlParser/XmlNode.hpp"
#include "DataStructures/KeyFrameData.hpp"

class AnimationLoader {

private:
    static glm::mat4 CORRECTION;
    XmlNode * _animationData;
    XmlNode * _jointHierarchy;

public:
    AnimationLoader(XmlNode * animationData, XmlNode * jointHierarchy);
    AnimationData extractAnimation();

private:
    std::vector<float> getKeyTimes();
    std::vector<KeyFrameData> initKeyFrames(std::vector<float> times);
    void loadJointTransforms(std::vector<KeyFrameData> frames, XmlNode * jointData, std::string rootNodeId);
    std::string getDataID(XmlNode * jointData);
    std::string getJointName(XmlNode * jointData);
    void processTransforms(std::string jointName, std::vector<std::string> rawData, std::vector<KeyFrameData> & keyFrames, bool root);
    std::string findRootJointName();
};

#endif