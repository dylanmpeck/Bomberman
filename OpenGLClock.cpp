/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   OpenGLClock.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpeck <dpeck@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/05 21:19:27 by dpeck             #+#    #+#             */
/*   Updated: 2019/07/05 21:22:55 by dpeck            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "OpenGLClock.hpp"

double OpenGLClock::lastFrameTime = 0.0f;
double OpenGLClock::delta = 0.0f;

void OpenGLClock::update()
{
    double currentFrameTime = glfwGetTime();
    delta = (currentFrameTime - lastFrameTime) / 1000.0f;
    lastFrameTime = currentFrameTime;
}

double OpenGLClock::getFrameTime()
{
    return delta;
}

double OpenGLClock::getCurrentTime()
{
    return (glfwGetTime());
}