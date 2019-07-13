/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Mesh.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpeck <dpeck@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/12 15:28:40 by dpeck             #+#    #+#             */
/*   Updated: 2019/07/12 15:55:51 by dpeck            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Mesh.hpp"
#include "GLDebug.hpp"

Mesh::Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures)
{
    this->_vertices = vertices;
    this->_indices = indices;
    this->_textures = textures;

    setupMesh();
}

void Mesh::setupMesh()
{
    GLCall(glGenVertexArrays(1, &_vao));
    GLCall(glGenBuffers(1, &_vbo));
    GLCall(glGenBuffers(1, &_ibo));

    GLCall(glBindVertexArray(_vao));
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, _vbo));

    GLCall(glBufferData(GL_ARRAY_BUFFER, _vertices.size() * sizeof(Vertex), &_vertices[0], GL_STATIC_DRAW));

    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ibo));
    GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, _indices.size() * sizeof(unsigned int), &_indices[0], GL_STATIC_DRAW));

    GLCall(glEnableVertexAttribArray(0));
    GLCall(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)0));

    GLCall(glEnableVertexAttribArray(1));
    GLCall(glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex, normal)));

    GLCall(glEnableVertexAttribArray(2));
    GLCall(glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex, texCoords)));

    GLCall(glBindVertexArray(0));
}

void Mesh::draw(Shader * shader)
{
    unsigned int diffuseNum = 1;
    unsigned int specularNum = 1;
    for (unsigned int i = 0; i < _textures.size(); i++)
    {
        GLCall(glActiveTexture(GL_TEXTURE0 + i));
        std::string number;
        std::string name = _textures[i].type;
        if (name == "texture_diffuse")
            number = std::to_string(diffuseNum++);
        else if (name == "texture_specular")
            number = std::to_string(specularNum++);
        shader->setUniform1i("material." + name + number, i);
        GLCall(glBindTexture(GL_TEXTURE_2D, _textures[i].id));
    }
    GLCall(glActiveTexture(GL_TEXTURE0));

    GLCall(glBindVertexArray(_vao));
    GLCall(glDrawElements(GL_TRIANGLES, _indices.size(), GL_UNSIGNED_INT, 0));
    GLCall(glBindVertexArray(0));
}