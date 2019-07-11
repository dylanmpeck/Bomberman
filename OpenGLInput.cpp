/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   OpenGLInput.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpeck <dpeck@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/10 19:17:15 by dpeck             #+#    #+#             */
/*   Updated: 2019/07/09 17:31:04 by dpeck            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "OpenGLInput.hpp"

unsigned int OpenGLInput::_curMenuChoice = 0;

OpenGLInput::OpenGLInput()
{
    return;
}

OpenGLInput::~OpenGLInput()
{
    return;
}

OpenGLInput::OpenGLInput(OpenGLInput const & other)
{
    static_cast<void>(other);
    throw(std::exception());
}

OpenGLInput const & OpenGLInput::operator=(OpenGLInput const & rhs)
{
    throw(std::exception());
    return (rhs);
}

void OpenGLInput::gameInput(Direction & curDirection)
{
    glfwPollEvents();

    //handles "X"ing out the window
    if (glfwWindowShouldClose(glfwGetCurrentContext()))
    {
        curDirection = Exit;
        return;
    }

    if (Callback::_keys[GLFW_KEY_UP] && curDirection != Down)
        curDirection = Up;
    else if (Callback::_keys[GLFW_KEY_RIGHT] && curDirection != Left)
        curDirection = Right;
    else if (Callback::_keys[GLFW_KEY_LEFT] && curDirection != Right)
        curDirection = Left;
    else if (Callback::_keys[GLFW_KEY_DOWN] && curDirection != Up)
        curDirection = Down;

    /* if (Callback::_keys[GLFW_KEY_ESCAPE])
        curDirection = Pause;*/
}