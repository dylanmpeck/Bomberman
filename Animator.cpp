/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Animator.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpeck <dpeck@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/05 20:55:46 by dpeck             #+#    #+#             */
/*   Updated: 2019/07/06 12:24:34 by dpeck            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Animator.hpp"
#include <math.h>

Animator::Animator(AnimatedModel entity) :
    _entity(entity), _currentAnimation(nullptr), _animationTime(0.0f)
{

}

void Animator::doAnimation(Animation * animation)
{
    this->_animationTime = 0.0f;
    this->_currentAnimation = animation;
}

void Animator::update()
{
    if (_currentAnimation == nullptr)
        return;
    increaseAnimationTime();
    std::unordered_map<std::string, glm::mat4> currentPose = calculateCurrentAnimationPose();
    applyPoseToJoints(currentPose, _entity.getRootJoint(), glm::mat4());
}

void Animator::increaseAnimationTime()
{
    _animationTime += OpenGLClock::getFrameTime();
    if (_animationTime > _currentAnimation->getLength())
        this->_animationTime = fmod(this->_animationTime, _currentAnimation->getLength());
}

std::unordered_map<std::string, glm::mat4> Animator::calculateCurrentAnimationPose()
{
    std::vector<KeyFrame> frames = getPreviousAndNextFrames();
    float progression = calculateProgression(frames[0], frames[1]);
    return interpolatePoses(frames[0], frames[1], progression);
}

void Animator::applyPoseToJoints(std::unordered_map<std::string, glm::mat4> currentPose, Joint joint, glm::mat4 parentTransform)
{
    glm::mat4 currentLocalTransform = currentPose[joint._name];
    glm::mat4 currentTransform = parentTransform * currentLocalTransform;
    for (Joint childJoint : joint._children)
        applyPoseToJoints(currentPose, childJoint, currentTransform);
    currentTransform = currentTransform * joint.getInverseBindTransform();
    joint.setAnimationTransform(currentTransform);
}

std::vector<KeyFrame> Animator::getPreviousAndNextFrames()
{
    std::vector<KeyFrame> allFrames = _currentAnimation->getKeyFrames();
    KeyFrame previousFrame = allFrames[0];
    KeyFrame nextFrame = allFrames[0];
    for (int i = 1; i < allFrames.size(); i++)
    {
        nextFrame = allFrames[i];
        if (nextFrame.getTimeStamp() > _animationTime)
            break;
        previousFrame = allFrames[i];
    }
    std::vector<KeyFrame> ret;
    ret.push_back(previousFrame);
    ret.push_back(nextFrame);
    return (ret);
}

float Animator::calculateProgression(KeyFrame previousFrame, KeyFrame nextFrame)
{
    float totalTime = nextFrame.getTimeStamp() - previousFrame.getTimeStamp();
    float currentTime = _animationTime - previousFrame.getTimeStamp();
    return (currentTime / totalTime);
}

std::unordered_map<std::string, glm::mat4> Animator::interpolatePoses(KeyFrame previousFrame, KeyFrame nextFrame, float progression)
{
    std::unordered_map<std::string, glm::mat4> currentPose;
    for (std::pair<std::string, JointTransform> jointName : previousFrame.getJointKeyFrames())
    {
        JointTransform previousTransform = previousFrame.getJointKeyFrames().at(jointName.first);
        JointTransform nextTransform = nextFrame.getJointKeyFrames().at(jointName.first);
        JointTransform currentTransform = JointTransform::interpolate(previousTransform, nextTransform, progression);
        currentPose[jointName.first] = currentTransform.getLocalTransform();
    }
    return (currentPose);
}

