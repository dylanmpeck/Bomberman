/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SkeletonData.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpeck <dpeck@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/06 16:56:31 by dpeck             #+#    #+#             */
/*   Updated: 2019/07/06 16:57:27 by dpeck            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SKELETONDATA_HPP
#define SKELETONDATA_HPP

#include "JointData.hpp"

class SkeletonData {

public:
    int _jointCount;
    JointData _headJoint;

    SkeletonData(int jointCount, JointData headJoint);
};

#endif