/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Animation.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpeck <dpeck@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/05 20:02:31 by dpeck             #+#    #+#             */
/*   Updated: 2019/07/10 16:50:45 by dpeck            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ANIMATION_HPP
#define ANIMATION_HPP

#include <vector>
#include <unordered_map>
#include <string>
#include "JointTransform.hpp"

class KeyFrame {

private:
    float _timeStamp;
    std::unordered_map<std::string, JointTransform *> _pose;

public:
    KeyFrame(KeyFrame const &);
    KeyFrame const & operator=(KeyFrame const &);
    KeyFrame(float timeStamp, std::unordered_map<std::string, JointTransform *> jointKeyFrames);
    float getTimeStamp();
    std::unordered_map<std::string, JointTransform *> getJointKeyFrames();

};

class Animation {

private:
    const float _length;
    const std::vector<KeyFrame> _keyFrames;

public:
    Animation(float lengthInSeconds, std::vector<KeyFrame> frames);
    float getLength();
    std::vector<KeyFrame> getKeyFrames();
};

#endif