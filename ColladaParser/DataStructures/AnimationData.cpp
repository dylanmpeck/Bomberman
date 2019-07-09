/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AnimationData.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpeck <dpeck@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/06 15:31:27 by dpeck             #+#    #+#             */
/*   Updated: 2019/07/06 15:32:00 by dpeck            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "AnimationData.hpp"

AnimationData::AnimationData(float lengthSeconds, std::vector<KeyFrameData> keyFrames) :
    _lengthSeconds(lengthSeconds), _keyFrames(keyFrames)
{

}