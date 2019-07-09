/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   KeyFrameData.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpeck <dpeck@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/06 15:49:51 by dpeck             #+#    #+#             */
/*   Updated: 2019/07/06 15:50:42 by dpeck            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "KeyFrameData.hpp"

KeyFrameData::KeyFrameData(float time) : _time(time)
{

}

void KeyFrameData::addJointTransform(JointTransformData transform)
{
    _jointTransforms.push_back(transform);
}