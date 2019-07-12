/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   VertexArray.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpeck <dpeck@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/26 15:26:01 by dpeck             #+#    #+#             */
/*   Updated: 2019/07/11 17:58:56 by dpeck            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "VertexArray.hpp"
#include "GLDebug.hpp"

VertexArray::VertexArray() : _indexBuffer(nullptr), _verticesCount(0)
{
    GLCall(glGenVertexArrays(1, &_rendererID));
}

VertexArray::~VertexArray() 
{
    if (_indexBuffer != nullptr)
        delete _indexBuffer;

    for (VertexBuffer * buffer : _dataVBOs)
        delete buffer;
    
    GLCall(glDeleteVertexArrays(1, &_rendererID));
}

VertexArray::VertexArray(VertexArray const & other)
{
    *this = other;
}

VertexArray const & VertexArray::operator=(VertexArray const & rhs)
{
    if (this != &rhs)
    {
        this->_rendererID = rhs._rendererID;
        this->_dataVBOs = rhs._dataVBOs;
        this->_indexBuffer = rhs._indexBuffer;
        this->_indexCount = rhs._indexCount;
        this->_verticesCount = rhs._verticesCount;
    }
    return (*this);
}

void VertexArray::createIndexBuffer(std::vector<unsigned int> indices)
{
    this->_indexBuffer = new IndexBuffer(&indices[0], indices.size());
    this->_indexCount = indices.size();
}

void VertexArray::createAttribute(int attribute, std::vector<float> data, int attrSize)
{
    //VertexBuffer vbo(&data[0], data.size() * sizeof(float), GL_STATIC_DRAW);
    _dataVBOs.push_back(new VertexBuffer(&data[0], data.size() * sizeof(float), GL_STATIC_DRAW));
    GLCall(glEnableVertexAttribArray(attribute));
    _dataVBOs.back()->bind();
    GLCall(glVertexAttribPointer(attribute, attrSize, GL_FLOAT, false, attrSize * sizeof(GLfloat), 0));
    _dataVBOs.back()->unbind();
    _verticesCount += data.size();
    //_dataVBOs.push_back(vbo);
}

void VertexArray::createIntAttribute(int attribute, std::vector<int> data, int attrSize)
{
    //VertexBuffer vbo(&data[0], data.size() * sizeof(float), GL_STATIC_DRAW);
    _dataVBOs.push_back(new VertexBuffer(&data[0], data.size() * sizeof(int), GL_STATIC_DRAW));
    GLCall(glEnableVertexAttribArray(attribute));
    _dataVBOs.back()->bind();
    GLCall(glVertexAttribIPointer(attribute, attrSize, GL_INT, attrSize * sizeof(GLint), 0));
    _dataVBOs.back()->unbind();
    _verticesCount += data.size();
    //_dataVBOs.push_back(vbo);    
}

void VertexArray::addBuffer(const VertexBuffer & vb, const VertexBufferLayout & layout)
{
    bind();
    vb.bind();
    const auto & elements = layout.getElements();
    uintptr_t offset = 0;
    for (unsigned int i = 0; i < elements.size(); i++)
    {
        const auto & element = elements[i];
        GLCall(glEnableVertexAttribArray(i));
        if (element.type == GL_FLOAT)
            GLCall(glVertexAttribPointer(i, element.count, element.type, element.normalized, 
            layout.getStride(), (void *)offset));
        //else
        //   GLCall(glVertexAttribIPointer(i, element.count, element.type, layout.getStride(), (void *)offset));
        
        offset += element.count * VertexBufferElement::getSizeOfType(element.type);
    }
}

void VertexArray::bind() const
{
    GLCall(glBindVertexArray(_rendererID));
}

void VertexArray::bind(std::vector<unsigned int> attributes)
{
    bind();
    for (unsigned int i = 0; i < attributes.size(); i++)
    {
        glEnableVertexAttribArray(i);
        _dataVBOs[i]->bind();
    }
}

void VertexArray::unbind() const
{
    GLCall(glBindVertexArray(0));
}

void VertexArray::unbind(std::vector<unsigned int> attributes)
{
    for (unsigned int i = 0; i < attributes.size(); i++)
        glDisableVertexAttribArray(i);
    unbind();
}

int VertexArray::getIndexCount()
{
    /*if (_indexBuffer)
        std::cout << "good" << std::endl;
    std::cout << _indexCount << std::endl;*/
    return (_indexCount);
}

unsigned int VertexArray::getVerticesCount()
{
    return (_verticesCount);
}

IndexBuffer * VertexArray::getIndexBuffer()
{
    return (_indexBuffer);
}