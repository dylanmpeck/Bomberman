/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AnimationLoader.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpeck <dpeck@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/09 15:57:52 by dpeck             #+#    #+#             */
/*   Updated: 2019/07/09 19:06:29 by dpeck            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "AnimationLoader.hpp"
#include <unordered_map>
#include "ColladaParser/ColladaLoader/ColladaLoader.hpp"
#include "ColladaParser/DataStructures/AnimationData.hpp"

Animation AnimationLoader::loadAnimation(std::string colladaFile)
{
    AnimationData animationData = ColladaLoader::loadColladaAnimation(colladaFile);
    std::vector<KeyFrame> frames;
    for (unsigned int i = 0; i < animationData._keyFrames.size(); i++)
        frames.push_back(createKeyFrame(animationData._keyFrames[i]));
    return (Animation(animationData._lengthSeconds, frames));
}

KeyFrame AnimationLoader::createKeyFrame(KeyFrameData data)
{
    std::unordered_map<std::string, JointTransform *> map;
    for (JointTransformData jointData : data._jointTransforms)
    {
        JointTransform jointTransform = createTransform(jointData);
        map[jointData._jointNameID] = &jointTransform;
    }
    return (KeyFrame(data._time, map));
}

JointTransform AnimationLoader::createTransform(JointTransformData data)
{
    glm::mat4 mat = data._jointLocalTransform;
    glm::vec3 translation(mat[3][0], mat[3][1], mat[3][2]);
    Quaternion rotation = Quaternion::fromMatrix(mat);
    return (JointTransform(translation, rotation));
}