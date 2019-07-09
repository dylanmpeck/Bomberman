/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AnimatedModel.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpeck <dpeck@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/04 18:55:05 by dpeck             #+#    #+#             */
/*   Updated: 2019/07/06 15:40:35 by dpeck            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "AnimatedModel.hpp"

AnimatedModel::AnimatedModel(VertexArray * model, Texture * texture, Joint rootJoint, int jointCount) :
    _model(model), _texture(texture), _rootJoint(rootJoint), _jointCount(jointCount),
    _animator(new Animator(*this))
{
    _rootJoint.calcInverseBindTransform(glm::mat4(1.0f));
}

AnimatedModel::~AnimatedModel()
{
    if (_animator != nullptr)
        delete _animator;
}

const VertexArray * AnimatedModel::getModel()
{
    return (_model);
}

const Texture * AnimatedModel::getTexture()
{
    return (_texture);
}

Joint AnimatedModel::getRootJoint()
{
    return (_rootJoint);
}

//won't need this unless things get restructured
void AnimatedModel::deleteOpenGL()
{
    delete _model;
    delete _texture;
}

void AnimatedModel::doAnimation(Animation * animation)
{
    _animator->doAnimation(animation);
}

void AnimatedModel::update()
{
    _animator->update();
}

std::vector<glm::mat4> AnimatedModel::getJointTransforms()
{
    std::vector<glm::mat4> jointMatrices;
    for (int i = 0; i < _jointCount; i++)
        jointMatrices.push_back(glm::mat4(1.0f));
    addJointsToArray(_rootJoint, jointMatrices);
    return (jointMatrices);
}

void AnimatedModel::addJointsToArray(const Joint & headJoint, std::vector<glm::mat4> & jointMatrices)
{
    jointMatrices[headJoint._index] = headJoint.getAnimatedTransform();
    for (Joint childJoint : headJoint._children)
        addJointsToArray(childJoint, jointMatrices);
}