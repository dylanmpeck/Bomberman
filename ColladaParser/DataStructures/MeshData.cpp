/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MeshData.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpeck <dpeck@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/06 16:51:44 by dpeck             #+#    #+#             */
/*   Updated: 2019/07/10 18:13:15 by dpeck            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MeshData.hpp"

const int MeshData::DIMENSIONS = 3;

MeshData::MeshData(std::vector<float> vertices, std::vector<float> textureCoords, std::vector<float> normals, 
                std::vector<unsigned int> indices, std::vector<int> jointIDs, std::vector<float> vertexWeights)
{
    this->_vertices = vertices;
    this->_textureCoords = textureCoords;
    this->_normals = normals;
    this->_indices = indices;
    this->_jointIDs = jointIDs;
    this->_vertexWeights = vertexWeights;
}

std::vector<int> MeshData::getJointIDs()
{
    return (_jointIDs);
}

std::vector<float> MeshData::getVertexWeights()
{
    return (_vertexWeights);
}

std::vector<float> MeshData::getVertices()
{
    return (_vertices);
}

std::vector<float> MeshData::getTextureCoords()
{
    return (_textureCoords);
}

std::vector<float> MeshData::getNormals()
{
    return (_normals);
}

std::vector<unsigned int> MeshData::getIndices()
{
    return (_indices);
}

int MeshData::getVertexCount()
{
    return (_vertices.size() / DIMENSIONS);
}