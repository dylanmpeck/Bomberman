/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AnimationLoader.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpeck <dpeck@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/09 15:55:35 by dpeck             #+#    #+#             */
/*   Updated: 2019/07/09 16:15:46 by dpeck            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ANIMATIONLOADER_HPP
#define ANIMATIONLOADER_HPP

#include <string>
#include "Animation.hpp"
#include "ColladaParser/DataStructures/KeyFrameData.hpp"
#include "ColladaParser/DataStructures/JointTransformData.hpp"

class AnimationLoader {

public:
    static Animation loadAnimation(std::string colladaFile);
    static KeyFrame createKeyFrame(KeyFrameData data);
    static JointTransform createTransform(JointTransformData data);

};

#endif