/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   OpenGLClock.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpeck <dpeck@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/05 21:17:25 by dpeck             #+#    #+#             */
/*   Updated: 2019/07/05 21:22:37 by dpeck            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OPENGLCLOCK_HPP
#define OPENGLCLOCK_HPP

#include "GLFW/glfw3.h"

class OpenGLClock {

private:
    static double lastFrameTime;
    static double delta;

public:
    static void update();
    static double getFrameTime();
    static double getCurrentTime();

};

#endif