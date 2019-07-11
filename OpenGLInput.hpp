/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   OpenGLInput.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpeck <dpeck@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/10 19:15:53 by dpeck             #+#    #+#             */
/*   Updated: 2019/07/09 17:29:57 by dpeck            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OPENGLINPUT_HPP
#define OPENGLINPUT_HPP

#include "Callbacks.hpp"
#include "GLFW/glfw3.h"
#include "eDirection.hpp"
#include <string>
#include <iostream>

class OpenGLInput {

private:
    static unsigned int _curMenuChoice;

public:
    static void gameInput(Direction & curDirection);
    //static void getMode(Direction & direction);

    ~OpenGLInput();

private:
    OpenGLInput();
    OpenGLInput(OpenGLInput const &);
    OpenGLInput const & operator=(OpenGLInput const &);

};

#endif