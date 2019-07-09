/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   JointTransform.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpeck <dpeck@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/05 20:19:03 by dpeck             #+#    #+#             */
/*   Updated: 2019/07/05 20:51:12 by dpeck            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "JointTransform.hpp"

JointTransform::JointTransform(glm::vec3 position, Quaternion rotation) :
    _position(position), _rotation(rotation)
{

}

glm::mat4 JointTransform::getLocalTransform()
{
    // might need to be identity matrix
    glm::mat4 matrix;
    glm::translate(matrix, _position);
    matrix = matrix * _rotation.toRotationMatrix();
    return (matrix);
}


//maybe should use pointers for these?
JointTransform JointTransform::interpolate(JointTransform frameA, JointTransform frameB, float progression)
{
    glm::vec3 pos = interpolate(frameA._position, frameB._position, progression);
    Quaternion rot = Quaternion::interpolate(frameA._rotation, frameB._rotation, progression);
    return JointTransform(pos, rot);
}

glm::vec3 interpolate(glm::vec3 start, glm::vec3 end, float progression)
{
    float x = start.x + (end.x - start.x) * progression;
    float y = start.y + (end.y - start.y) * progression;
    float z = start.z + (end.z - start.z) * progression;
    return (glm::vec3(x, y, x));
}

