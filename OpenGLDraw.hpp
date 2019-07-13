/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   OpenGLDraw.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpeck <dpeck@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/10 14:43:55 by dpeck             #+#    #+#             */
/*   Updated: 2019/07/12 17:44:54 by dpeck            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OPENGLDRAW_HPP
#define OPENGLDRAW_HPP

#include "glad/glad.h"
#include "vendor/glm/glm.hpp"
#include "vendor/glm/gtc/matrix_transform.hpp"
#include "GLFW/glfw3.h"

#include "TextRenderer.hpp"
#include <vector>
#include <unordered_map>

class OpenGLDraw {

private:
    static std::shared_ptr<TextRenderer> _textRenderer;

    static VertexBufferLayout _layouts[3];
    static std::vector<unsigned int> _offsets[3];
    
public:

    static void buildVertexBufferLayouts();
    static void buildTextRenderer();

    static void clearScreen();
    static void swapBuffers();

    //static void render(AnimatedModel * entity);

    static VertexBufferLayout & getBufferLayout(unsigned int slot);
    static std::vector<unsigned int> & getBufferFormat(unsigned int slot);

    ~OpenGLDraw();

private:
    OpenGLDraw();
    OpenGLDraw(OpenGLDraw const &);
    OpenGLDraw const & operator=(OpenGLDraw const &);
};

#endif