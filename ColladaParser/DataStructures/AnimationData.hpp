/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AnimationData.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpeck <dpeck@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/06 15:29:51 by dpeck             #+#    #+#             */
/*   Updated: 2019/07/06 18:01:23 by dpeck            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ANIMATIONDATA_HPP
#define ANIMATIONDATA_HPP

#include <vector>
#include "KeyFrameData.hpp"

class AnimationData {

public:
    float _lengthSeconds;
    std::vector<KeyFrameData> _keyFrames;

    AnimationData(float lengthSeconds, std::vector<KeyFrameData> keyFrames);
};

#endif