/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   VertexArray.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpeck <dpeck@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/26 15:08:24 by dpeck             #+#    #+#             */
/*   Updated: 2019/07/10 19:46:11 by dpeck            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VERTEXARRAY_HPP
#define VERTEXARRAY_HPP

#include <vector>
#include "VertexBuffer.hpp"
#include "IndexBuffer.hpp"
#include "VertexBufferLayout.hpp"

class VertexArray {

private:
    unsigned int _rendererID;
    std::vector<VertexBuffer *> _dataVBOs;
    IndexBuffer * _indexBuffer;
    int _indexCount;
    unsigned int _verticesCount;

public:
    VertexArray();
    ~VertexArray();

    void createIndexBuffer(std::vector<unsigned int> indices);
    void createAttribute(int attribute, std::vector<float> data, int attrSize);
    void createIntAttribute(int attribute, std::vector<int> data, int attrSize);

    void addBuffer(const VertexBuffer & vb, const VertexBufferLayout & layout);

    void bind() const;
    void bind(std::vector<unsigned int> attributes);
    void unbind() const;
    void unbind(std::vector<unsigned int> attributes);

    int getIndexCount();
    unsigned int getVerticesCount();
    IndexBuffer * getIndexBuffer();

private:
    VertexArray(VertexArray const &);
    VertexArray const & operator=(VertexArray const &);

};

#endif