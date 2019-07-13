/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ResourceManager.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpeck <dpeck@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/29 19:47:19 by dpeck             #+#    #+#             */
/*   Updated: 2019/07/12 17:10:12 by dpeck            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RESOURCEMANAGER_HPP
#define RESOURCEMANAGER_HPP

#include <map>
#include <string>

#include "glad/glad.h"

#include "TextureLoader.hpp"
#include "Shader.hpp"
#include "Camera.hpp"

#include "vendor/glm/glm.hpp"
#include "vendor/glm/gtc/matrix_transform.hpp"

class ResourceManager {

public:
    static std::map<std::string, Shader> _shaders;
    static std::map<std::string, TextureLoader> _textures;
    static std::map<std::string, Camera> _cameras;
    //static std::map<std::string, IndexBuffer> _indexBuffers;
    //static std::map<std::string, VertexArray> _vertexArrays;

    static Shader & loadShader(const std::string & filePath, const std::string & name);
    static Shader & getShader(const std::string & name);
    static TextureLoader & loadTexture(const std::string & filePath, const std::string & name);
    static TextureLoader & loadTexture(const std::string & filePath, const std::string & dirPath, const std::string & name);
    static TextureLoader & getTexture(const std::string & name);
    static Camera & loadCamera(const std::string & name, glm::vec3 pos);
    static Camera & getCamera(const std::string & name);
    //static IndexBuffer & loadIndexBuffer(const std::string & name);
    //static IndexBuffer & getIndexBuffer(const std::string & name);
    //static VertexArray & loadVertexArray(const std::string & name, unsigned int size);
    //static VertexArray & getVertexArray(const std::string & name);
    static ShaderProgramSource parseShader(const std::string & filePath); // should be moved to private later

    static void clear();

    ~ResourceManager();

private:
    static TextureLoader _texture;
    ResourceManager();
    ResourceManager(ResourceManager const &);
    ResourceManager const & operator=(ResourceManager const &);

    static TextureLoader & loadTextureFromFile(const std::string & filePath);
};

#endif
