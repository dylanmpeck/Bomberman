/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Callbacks.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpeck <dpeck@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/06 19:21:41 by dpeck             #+#    #+#             */
/*   Updated: 2019/07/11 18:43:06 by dpeck            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CALLBACKS_HPP
#define CALLBACKS_HPP

#include "glad/glad.h"
#include "Camera.hpp"
#include "GLFW/glfw3.h"
#include "GLDebug.hpp"

class Callback {

public:
    static bool _keys[1024];

    static void framebufferSizeCallback(GLFWwindow * window, int width, int height);

    static void keyCallback(GLFWwindow * window, int key, int scancode, int action, int mode);
    static void mouseCallback(GLFWwindow * window, double xpos, double ypos);

    ~Callback();

private:
    Callback();
    Callback(Callback const &);
    Callback const & operator=(Callback const &);

};

#endif