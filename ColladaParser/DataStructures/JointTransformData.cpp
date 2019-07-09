/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   JointTransformData.cpp                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpeck <dpeck@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/06 15:47:25 by dpeck             #+#    #+#             */
/*   Updated: 2019/07/06 15:48:06 by dpeck            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "JointTransformData.hpp"

JointTransformData::JointTransformData(std::string jointNameID, glm::mat4 jointLocalTransform) :
    _jointNameID(jointNameID), _jointLocalTransform(jointLocalTransform)
{
    
}