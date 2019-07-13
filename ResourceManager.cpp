/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ResourceManager.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpeck <dpeck@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/29 19:59:37 by dpeck             #+#    #+#             */
/*   Updated: 2019/07/12 17:11:14 by dpeck            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ResourceManager.hpp"
#include "vendor/stb_image/stb_image.h"
#include <fstream>
#include <sstream>

std::map<std::string, TextureLoader> ResourceManager::_textures;
std::map<std::string, Shader> ResourceManager::_shaders;
std::map<std::string, Camera> ResourceManager::_cameras;
//std::map<std::string, IndexBuffer> ResourceManager::_indexBuffers;
//std::map<std::string, VertexArray> ResourceManager::_vertexArrays;

TextureLoader ResourceManager::_texture;

ResourceManager::ResourceManager() { return; }

ResourceManager::~ResourceManager() { return; }

ResourceManager::ResourceManager(ResourceManager const & other)
{
	static_cast<void>(other);
	throw(std::exception());
}

ResourceManager const & ResourceManager::operator=(ResourceManager const & rhs)
{
	throw(std::exception());
	return (rhs);
}

Shader & ResourceManager::loadShader(const std::string & filePath, const std::string & name)
{
    ShaderProgramSource source = parseShader(filePath);
    _shaders[name] = Shader(source);
    return (_shaders[name]);
}

ShaderProgramSource ResourceManager::parseShader(const std::string & filePath)
{
	std::ifstream stream(filePath);

	enum class ShaderType
	{
		NONE = -1, VERTEX = 0, FRAGMENT = 1
	};

	std::string line;
	std::stringstream ss[2];
	ShaderType type = ShaderType::NONE;
	while (std::getline(stream, line))
	{
		if (line.find("#shader") != std::string::npos)
		{
			if (line.find("vertex") != std::string::npos)
				type = ShaderType::VERTEX;
			else if (line.find("fragment") != std::string::npos)
				type = ShaderType::FRAGMENT;
		}
		else
			ss[static_cast<int>(type)] << line << '\n';
	}

	return {ss[0].str(), ss[1].str()};    
}

TextureLoader & ResourceManager::loadTexture(const std::string & filePath, const std::string & name)
{
    _textures[name] = loadTextureFromFile(filePath);
    return (_textures[name]);
}

TextureLoader & ResourceManager::loadTexture(const std::string & filePath, const std::string & dirPath, const std::string & name)
{
	std::string filename = dirPath + '/' + filePath;
    _textures[name] = loadTextureFromFile(filename);
    return (_textures[name]);
}

TextureLoader & ResourceManager::loadTextureFromFile(const std::string & filePath)
{
    unsigned char *buffer = nullptr;
    int width, height, nbrComponents;
    //stbi_set_flip_vertically_on_load(1);
    buffer = stbi_load(filePath.c_str(), &width, &height, &nbrComponents, 4);

    _texture = TextureLoader(width, height, buffer, nbrComponents);

    if (buffer != nullptr)
        stbi_image_free(buffer);

    return (_texture);
}

Shader & ResourceManager::getShader(const std::string & name)
{
	if (_shaders.find(name) != _shaders.end())
		return (_shaders[name]);
    return (getShader("default"));
}

TextureLoader & ResourceManager::getTexture(const std::string & name)
{
	if (_textures.find(name) != _textures.end())
		return (_textures[name]);
    return (getTexture("triangle"));
}

Camera & ResourceManager::loadCamera(const std::string & name, glm::vec3 pos)
{
	_cameras[name] = Camera(pos);
	return (_cameras[name]);
}

Camera & ResourceManager::getCamera(const std::string & name)
{
	if (_cameras.find(name) != _cameras.end())
		return (_cameras[name]);
	return (_cameras["null"]);
}

/*IndexBuffer & ResourceManager::loadIndexBuffer(const std::string & name)
{
	_indexBuffers[name] = IndexBuffer(Shape::quadIndices, Shape::quadIndicesCount);
	return (_indexBuffers[name]);
}

IndexBuffer & ResourceManager::getIndexBuffer(const std::string & name)
{
	if (_indexBuffers.find(name) != _indexBuffers.end())
		return (_indexBuffers[name]);
	return (getIndexBuffer("default"));
}

VertexArray & ResourceManager::loadVertexArray(const std::string & name, unsigned int size)
{
	VertexArray va;
	VertexBuffer vb(Shape::quad, size);
	IndexBuffer ib = loadIndexBuffer(name);
	VertexBufferLayout layout;
	unsigned int shapeSize = sizeof(Shape::quadLayout) / sizeof(Shape::quadLayout[0]);
	for (unsigned int i = 0; i < shapeSize; i++)
		layout.push<float>(Shape::quadLayout[i]);
	va.addBuffer(vb, layout);
	_vertexArrays[name] = va;
	return (_vertexArrays[name]);
}

VertexArray & ResourceManager::getVertexArray(const std::string & name)
{
	if (_vertexArrays.find(name) != _vertexArrays.end())
		return (_vertexArrays[name]);
	return (getVertexArray("default"));
}*/

void ResourceManager::clear()
{
	for (auto tex : _textures)
		tex.second.openGLDelete();
	for (auto shader : _shaders)
		shader.second.openGLDelete();
    //might need to implement this if memory leaks. but the shaders and textures should delete on destruction
    return;
}

