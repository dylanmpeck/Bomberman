/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   OpenGLInit.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpeck <dpeck@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/10 19:03:11 by dpeck             #+#    #+#             */
/*   Updated: 2019/07/11 19:20:26 by dpeck            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "OpenGLInit.hpp"
#include <iostream>
#include "ResourceManager.hpp"
#include "GLDebug.hpp"
#include "Callbacks.hpp"
#include "Camera.hpp"

//TODO need to set window variables somewhere
#define WINWIDTH 1280
#define WINHEIGHT 800

OpenGLInit::OpenGLInit()
{
	return;
}

OpenGLInit::~OpenGLInit()
{
	return;
}

OpenGLInit::OpenGLInit(OpenGLInit const & other)
{
	static_cast<void>(other);
	throw(std::exception());
}

OpenGLInit const & OpenGLInit::operator=(OpenGLInit const & rhs)
{
	throw(std::exception());
	return (rhs);
}

bool OpenGLInit::createWindow()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	GLFWwindow * window = glfwCreateWindow(WINWIDTH, WINHEIGHT, "Bomberman", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return (false);
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, Callback::framebufferSizeCallback);
	glfwSwapInterval(1); //synchronize with vsync
	glfwSetKeyCallback(window, Callback::keyCallback);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	ResourceManager::loadCamera("main", glm::vec3(0.0f, 0.0f, 2.5f));
	glfwSetCursorPosCallback(window, Callback::mouseCallback);

	//loads the address of OpenGL function pointers which are OS-specific
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return (false);
	}

	//GLCall(glViewport(0, 0, WINWIDTH, WINHEIGHT));
	GLCall(glEnable(GL_DEPTH_TEST));
	GLCall(glEnable(GL_CULL_FACE));
	GLCall(glEnable(GL_BLEND));
	GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

	return (true);   
}

void OpenGLInit::destroyWindow()
{
	glfwDestroyWindow(glfwGetCurrentContext());
	glfwTerminate();    
}

void OpenGLInit::clearResources()
{
	ResourceManager::clear();   
}

bool OpenGLInit::buildShaders()
{
	Shader *shader;
    Camera camera(glm::vec3(0.0f, 0.0f, 5.5f));
    
    //Animated Model shader
    shader = &ResourceManager::loadShader("./shaders/animatedModel.shader", "animatedModelShader");
	glm::mat4 model(1.0f);
	//model = glm::scale(model, glm::vec3(2.0f, 2.0f, 2.0f));
	glm::mat4 view = camera.getViewMatrix();
	//view = glm::rotate(view, glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	glm::mat4 proj = glm::perspective(glm::radians(45.0f), (float)(WINWIDTH)/(float)(WINHEIGHT), 0.1f, 100.0f);
	//glm::mat4 proj = glm::ortho(0.0f, static_cast<float>(WINWIDTH), static_cast<float>(WINHEIGHT), 0.0f, 0.1f, 10.0f);
    if (shader != nullptr)
    {
        shader->bind();
		//shader->setUniformMat4f("u_model", model);
        shader->setUniformMat4f("u_projection", proj);
		shader->setUniformMat4f("u_view", view);
		shader->setUniform3f("u_lightDirection", 0.2f, -0.3f, -0.8f); // TODO might want to do something fancier with lighting
    }
	else
		return (false);

	return (true);     
}

void OpenGLInit::buildTextures()
{
    ResourceManager::loadTexture("./textures/snake-graphics.png", GL_TRUE, GL_FALSE, "snake");
    ResourceManager::loadTexture("./textures/grass.png", GL_TRUE, GL_TRUE, "grass");
    ResourceManager::loadTexture("./textures/tree.png", GL_TRUE, GL_FALSE, "tree");    
}