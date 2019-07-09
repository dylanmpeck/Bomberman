/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SkeletonData.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpeck <dpeck@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/06 16:57:31 by dpeck             #+#    #+#             */
/*   Updated: 2019/07/06 16:58:01 by dpeck            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "SkeletonData.hpp"

SkeletonData::SkeletonData(int jointCount, JointData headJoint) :
    _jointCount(jointCount), _headJoint(headJoint)
{
    
}