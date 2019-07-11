/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Animator.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpeck <dpeck@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/05 20:52:37 by dpeck             #+#    #+#             */
/*   Updated: 2019/07/09 18:50:34 by dpeck            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ANIMATOR_HPP
#define ANIMATOR_HPP

#include <unordered_map>
#include "AnimatedModel.hpp"
#include "Animation.hpp"
#include "Joint.hpp"
#include "OpenGLClock.hpp"

class AnimatedModel;

class Animator {

private:
    AnimatedModel * _entity;
    Animation * _currentAnimation;
    float _animationTime;

public:
    Animator(AnimatedModel * entity);
    void doAnimation(Animation * animation);
    void update();

private:
    void increaseAnimationTime();
    std::unordered_map<std::string, glm::mat4> calculateCurrentAnimationPose();
    void applyPoseToJoints(std::unordered_map<std::string, glm::mat4> currentPose, Joint joint, glm::mat4 parentTransform);
    std::vector<KeyFrame> getPreviousAndNextFrames();
    float calculateProgression(KeyFrame previousFrame, KeyFrame nextFrame);
    std::unordered_map<std::string, glm::mat4> interpolatePoses(KeyFrame previousFrame, KeyFrame nextFrame, float progression);


};

#endif