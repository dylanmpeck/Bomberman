/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   OpenGLDraw.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpeck <dpeck@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/10 15:23:40 by dpeck             #+#    #+#             */
/*   Updated: 2019/07/11 19:01:49 by dpeck            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "OpenGLDraw.hpp"
#include "Callbacks.hpp"
#include "ResourceManager.hpp"
#include "Camera.hpp"
#include <sstream>

std::shared_ptr<TextRenderer> OpenGLDraw::_textRenderer = nullptr;

VertexBufferLayout OpenGLDraw::_layouts[3];
std::vector<unsigned int> OpenGLDraw::_offsets[3];

OpenGLDraw::OpenGLDraw()
{
    return;
}

OpenGLDraw::~OpenGLDraw()
{
    return;
}

OpenGLDraw::OpenGLDraw(OpenGLDraw const & other)
{
    static_cast<void>(other);
    throw(std::exception());
}

OpenGLDraw const & OpenGLDraw::operator=(OpenGLDraw const & rhs)
{
    throw(std::exception());
    return (rhs);
}


void OpenGLDraw::buildTextRenderer()
{
	//_textRenderer = static_cast<std::shared_ptr<TextRenderer>>(new TextRenderer(Gameboard::windowWidth, Gameboard::windowHeight));
    //_textRenderer->load("fonts/Stencil8bit-Regular.otf", Gameboard::squareSize + Gameboard::squareSize / 2);    
}

void OpenGLDraw::buildVertexBufferLayouts()
{
    //basic 2d
 	_layouts[0].push<float>(2);
	_offsets[0].push_back(2); 

    //2d textured
 	_layouts[1].push<float>(2);
	_offsets[1].push_back(2);
	_layouts[1].push<float>(2);
	_offsets[1].push_back(2);

    //3d version
	_layouts[2].push<float>(3);
	_offsets[2].push_back(3);
}

void OpenGLDraw::clearScreen()
{
	GLCall(glClearColor(0.0f, 0.0f, 0.0f, 1.0f));
	GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
}

void OpenGLDraw::swapBuffers()
{
	glfwSwapBuffers(glfwGetCurrentContext());    
}

VertexBufferLayout & OpenGLDraw::getBufferLayout(unsigned int slot)
{
    return (_layouts[slot]);
}

std::vector<unsigned int> & OpenGLDraw::getBufferFormat(unsigned int slot)
{
    return (_offsets[slot]);
}

void OpenGLDraw::render(AnimatedModel * entity)
{
    std::vector<unsigned int> numOfAttribs(5, 1);
    entity->getModel()->bind(numOfAttribs);
    entity->getTexture()->bind();
    entity->getModel()->getIndexBuffer()->bind();
    Shader * shader = &ResourceManager::getShader("animatedModelShader");
    shader->bind();
    shader->setUniform1i("u_diffuseMap", 0);
    Camera * camera = &ResourceManager::getCamera("main");
    shader->setUniformMat4f("u_view", camera->getViewMatrix());   
    unsigned int i = 0;
    for (glm::mat4 jointTransform : entity->getJointTransforms())
    {
        std::stringstream ss("");
        ss << "u_jointTransforms[" << i << "]";
        shader->setUniformMat4f(ss.str(), jointTransform);
        i++;
    }
    GLCall(glDrawElements(GL_TRIANGLES, entity->getModel()->getIndexCount(), GL_UNSIGNED_INT, 0));
    //glDrawArrays(GL_TRIANGLES, 0, entity->getModel()->getVerticesCount());
    //entity->getModel()->unbind(numOfAttribs);
}