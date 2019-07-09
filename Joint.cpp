/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Joint.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpeck <dpeck@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/04 18:20:56 by dpeck             #+#    #+#             */
/*   Updated: 2019/07/06 11:36:58 by dpeck            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Joint.hpp"

Joint::Joint(int index, std::string name, glm::mat4 bindLocalTransform) :
    _index(index), _name(name), _localBindTransform(bindLocalTransform)
{
}

//Adds a child to joint. Used during creation. All children of bones must be moved
void Joint::addChild(Joint child)
{
    _children.push_back(child);
}


// The animated transform is the transform that gets loaded up to the shader
glm::mat4 Joint::getAnimatedTransform() const
{
    return (_animatedTransform);
}


// Allows all joint transforms that make animation possible
void Joint::setAnimationTransform(glm::mat4 animationTransform)
{
    this->_animatedTransform = animationTransform;
}

glm::mat4 Joint::getInverseBindTransform() const
{
    return (_inverseBindTransform);
}

void Joint::calcInverseBindTransform(glm::mat4 parentBindTransform)
{
    glm::mat4 bindTransform = parentBindTransform * _localBindTransform;
    _inverseBindTransform = glm::inverse(bindTransform);
    for (Joint child : _children)
        child.calcInverseBindTransform(bindTransform);
}