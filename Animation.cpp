/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Animation.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpeck <dpeck@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/05 20:05:00 by dpeck             #+#    #+#             */
/*   Updated: 2019/07/06 11:54:53 by dpeck            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Animation.hpp"

Animation::Animation(float lengthInSeconds, std::vector<KeyFrame> frames) :
    _length(lengthInSeconds), _keyFrames(frames)
{

}

float Animation::getLength()
{
    return (_length);
}

std::vector<KeyFrame> Animation::getKeyFrames()
{
    return (_keyFrames);
}

KeyFrame::KeyFrame(KeyFrame const & other) :
    _timeStamp(other._timeStamp), _pose(other._pose)
{

}

KeyFrame const & KeyFrame::operator=(KeyFrame const & rhs)
{
    if (&rhs != this)
        return (KeyFrame(rhs));
    return (*this);
}

KeyFrame::KeyFrame(float timeStamp, std::map<std::string, JointTransform> jointKeyFrames) :
    _timeStamp(timeStamp), _pose(jointKeyFrames)
{

}

float KeyFrame::getTimeStamp()
{
    return (_timeStamp);
}

std::map<std::string, JointTransform> KeyFrame::getJointKeyFrames()
{
    return (_pose);
}