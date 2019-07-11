/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   JointTransform.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpeck <dpeck@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/05 20:19:03 by dpeck             #+#    #+#             */
/*   Updated: 2019/07/11 15:43:44 by dpeck            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "JointTransform.hpp"

JointTransform::JointTransform()
{
    this->_position = glm::vec3(0.0f);
}

JointTransform::JointTransform(glm::vec3 position, Quaternion rotation) :
    _position(position), _rotation(rotation)
{

}

JointTransform::~JointTransform()
{

}

JointTransform::JointTransform(const JointTransform & other) : _rotation(other._rotation)
{
    *this = other;
}

JointTransform const & JointTransform::operator=(const JointTransform & rhs)
{
    if (this != &rhs)
    {
        this->_position = rhs._position;
        this->_rotation = rhs._rotation;
    }
    return (*this);
}

glm::mat4 JointTransform::getLocalTransform()
{
    // might need to be identity matrix
    glm::mat4 matrix(1.0f);
    glm::translate(matrix, _position);
    matrix = matrix * _rotation.toRotationMatrix();
    return (matrix);
}


//maybe should use pointers for these?
JointTransform JointTransform::interpolate(JointTransform * frameA, JointTransform * frameB, float progression)
{
    glm::vec3 pos = interpolate(frameA->_position, frameB->_position, progression);
    Quaternion rot = Quaternion::interpolate(frameA->_rotation, frameB->_rotation, progression);
    return JointTransform(pos, rot);
}

glm::vec3 JointTransform::interpolate(glm::vec3 start, glm::vec3 end, float progression)
{
    float x = start.x + (end.x - start.x) * progression;
    float y = start.y + (end.y - start.y) * progression;
    float z = start.z + (end.z - start.z) * progression;
    return (glm::vec3(x, y, x));
}

