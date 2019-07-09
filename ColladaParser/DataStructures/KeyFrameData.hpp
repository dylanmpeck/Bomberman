/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   KeyFrameData.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpeck <dpeck@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/06 15:48:42 by dpeck             #+#    #+#             */
/*   Updated: 2019/07/06 15:49:46 by dpeck            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef KEYFRAMEDATA_HPP
#define KEYFRAMEDATA_HPP

#include <vector>
#include "JointTransformData.hpp"

class KeyFrameData {

public:
    float _time;
    std::vector<JointTransformData> _jointTransforms;

    KeyFrameData(float time);
    void addJointTransform(JointTransformData transform);
};

#endif