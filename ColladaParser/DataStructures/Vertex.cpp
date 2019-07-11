/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Vertex.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpeck <dpeck@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/06 17:07:12 by dpeck             #+#    #+#             */
/*   Updated: 2019/07/10 16:43:36 by dpeck            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Vertex.hpp"

const int Vertex::NO_INDEX = -1;

Vertex::~Vertex()
{
    //TODO MEMORY LEAKS?
    /*if (this->_duplicateVertex != nullptr)
        delete this->_duplicateVertex;
    if (this->_weightsData != nullptr)
        delete this->_weightsData;*/
}

Vertex::Vertex(Vertex const & other)
{
    *this = other;
}

Vertex const & Vertex::operator=(Vertex const & rhs)
{
    if (this != &rhs)
    {
        this->_position = glm::vec3(rhs._position);
        this->_textureIndex = rhs._textureIndex;
        this->_normalIndex = rhs._normalIndex;
        this->_duplicateVertex = new Vertex(*rhs._duplicateVertex);
        this->_index = rhs._index;
        this->_length = rhs._length;
        this->_tangents = rhs._tangents;
        this->_averagedTangent = rhs._averagedTangent;
        this->_weightsData = new VertexSkinData(*rhs._weightsData);       
    }
    return (*this);
}

Vertex::Vertex(int index, glm::vec3 position, VertexSkinData * weightsData)
{
    this->_textureIndex = NO_INDEX;
    this->_normalIndex = NO_INDEX;
    this->_duplicateVertex = nullptr;
    this->_averagedTangent = glm::vec3(0.0f);

    this->_index = index;
    this->_weightsData = weightsData;
    this->_position = position;
    this->_length = position.length();
}

VertexSkinData * Vertex::getWeightsData()
{
    return (_weightsData);
}

void Vertex::addTangent(glm::vec3 tangent)
{
    _tangents.push_back(tangent);
}

void Vertex::averageTangents()
{
    if (_tangents.empty())
        return;
    
    for (glm::vec3 tangent : _tangents)
    {
        _averagedTangent += tangent;
    }
    glm::normalize(_averagedTangent);
}

glm::vec3 Vertex::getAverageTangent()
{
    return (_averagedTangent);
}

int Vertex::getIndex()
{
    return (_index);
}

float Vertex::getLength()
{
    return (_length);
}

bool Vertex::isSet()
{
    return _textureIndex != NO_INDEX && _normalIndex != NO_INDEX;
}

bool Vertex::hasSameTextureAndNormal(int textureIndexOther, int normalIndexOther)
{
    return (textureIndexOther == _textureIndex && normalIndexOther == _normalIndex);
}

void Vertex::setTextureIndex(int textureIndex)
{
    this->_textureIndex = textureIndex;
}

void Vertex::setNormalIndex(int normalIndex)
{
    this->_normalIndex = normalIndex;
}

glm::vec3 Vertex::getPosition()
{
    return (_position);
}

int Vertex::getTextureIndex()
{
    return (_textureIndex);
}

int Vertex::getNormalIndex()
{
    return (_normalIndex);
}

Vertex * Vertex::getDuplicateVertex()
{
    return (_duplicateVertex);
}

void Vertex::setDuplicateVertex(Vertex * duplicateVertex)
{
    if (this->_duplicateVertex != nullptr)
        delete this->_duplicateVertex;
    this->_duplicateVertex = duplicateVertex;
}