/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   GeometryLoader.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpeck <dpeck@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/07 17:13:34 by dpeck             #+#    #+#             */
/*   Updated: 2019/07/10 19:19:14 by dpeck            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "GeometryLoader.hpp"
#include <string>
#include <iostream>

glm::mat4 GeometryLoader::CORRECTION = glm::rotate(glm::mat4(1.0f), glm::radians(-90.0f), glm::vec3(1.0, 0.0, 0.0));

GeometryLoader::GeometryLoader(pugi::xml_node geometryNode, std::vector<VertexSkinData *> vertexWeights)
{
    for (VertexSkinData * skinData : vertexWeights)
        this->_vertexWeights.push_back(skinData);
    this->_meshData = geometryNode.child("geometry").child("mesh");
}

GeometryLoader::~GeometryLoader()
{
    for (Vertex * vertex : _vertices)
        delete vertex;
}

MeshData GeometryLoader::extractModelData()
{
    readRawData();
    assembleVertices();
    removeUnusedVertices();
    initArrays();
    convertDataToArrays();
  //convertIndicesListToArray(); don't think this will be needed
    return (MeshData(_verticesArray, _texturesArray, _normalsArray, _indices, _jointIDsArray, _weightsArray));
}

void GeometryLoader::readRawData()
{
    readPositions();
    readNormals();
    readTextureCoords();
}

void GeometryLoader::readPositions()
{
    std::string positionsID = _meshData.child("vertices").child("input").attribute("source").value();
    positionsID = positionsID.substr(1);
    pugi::xml_node positionsData = _meshData.find_child_by_attribute("source", "id", positionsID.c_str()).child("float_array");
    int count = std::stoi(positionsData.attribute("count").value());

    std::string positionsDataStr = positionsData.child_value();
    std::vector<std::string> posData;
    size_t pos = 0;
    while ((pos = positionsDataStr.find(" ")) != std::string::npos)
    {
        posData.push_back(positionsDataStr.substr(0, pos));
        positionsDataStr.erase(0, pos + 1);
    }
    posData.push_back(positionsDataStr.substr(0, pos));
    std::cout << "Pos data: " << posData.back() << std::endl;

    for (int i = 0; i < count / 3; i++)
    {
        float x = std::stof(posData[i * 3]);
        float y = std::stof(posData[i * 3 + 1]);
        float z = std::stof(posData[i * 3 + 2]);
        glm::vec4 position(x, y, z, 1.0f);
        position = CORRECTION * position; // transform matrix by vector. might need to be flipped
        _vertices.push_back(new Vertex(_vertices.size(), glm::vec3(position.x, position.y, position.z), _vertexWeights[_vertices.size()]));
    }
}

void GeometryLoader::readNormals()
{
    std::string normalsID = _meshData.child("polylist").find_child_by_attribute("input", "semantic", "NORMAL").attribute("source").value();
    normalsID = normalsID.substr(1);
    pugi::xml_node normalsData = _meshData.find_child_by_attribute("source", "id", normalsID.c_str()).child("float_array");
    int count = std::stoi(normalsData.attribute("count").value());

    std::string normalsDataStr = normalsData.child_value();
    std::vector<std::string> normData;
    size_t pos = 0;
    while ((pos = normalsDataStr.find(" ")) != std::string::npos)
    {
        normData.push_back(normalsDataStr.substr(0, pos));
        normalsDataStr.erase(0, pos + 1);
    }
    normData.push_back(normalsDataStr.substr(0, pos));
    std::cout << "Norm data: " << normData.back() << std::endl;

    for (int i = 0; i < count / 3; i++)
    {
        float x = std::stof(normData[i * 3]);
        float y = std::stof(normData[i * 3 + 1]);
        float z = std::stof(normData[i * 3 + 2]);
        glm::vec4 norm(x, y, z, 0.0f);
        norm = CORRECTION * norm;
        _normals.push_back(glm::vec3(norm.x, norm.y, norm.z));
    }
}

void GeometryLoader::readTextureCoords()
{
    std::string texCoordsID = _meshData.child("polylist").find_child_by_attribute("input", "semantic", "TEXCOORD").attribute("source").value();
    texCoordsID = texCoordsID.substr(1);
    pugi::xml_node texCoordsData = _meshData.find_child_by_attribute("source", "id", texCoordsID.c_str()).child("float_array");
    int count = std::stoi(texCoordsData.attribute("count").value());

    std::string texCoordsDataStr = texCoordsData.child_value();
    std::vector<std::string> texData;
    size_t pos = 0;
    while ((pos = texCoordsDataStr.find(" ")) != std::string::npos)
    {
        texData.push_back(texCoordsDataStr.substr(0, pos));
        texCoordsDataStr.erase(0, pos + 1);
    }
    texData.push_back(texCoordsDataStr.substr(0, pos));
    std::cout << "Tex data: " << texData.back() << std::endl;

    for (int i = 0; i < count / 2; i++)
    {
        float s = std::stof(texData[i * 2]);
        float t = std::stof(texData[i * 2 + 1]);
        _textures.push_back(glm::vec2(s, t));
    }
}

void GeometryLoader::assembleVertices()
{
    pugi::xml_node poly = _meshData.child("polylist");
    int typeCount = 0;
    for (pugi::xml_node node : poly.children("input"))
        typeCount++;

    std::string polyDataStr = poly.child("p").child_value();
    std::vector<std::string> indexData;
    size_t pos = 0;
    while ((pos = polyDataStr.find(" ")) != std::string::npos)
    {
        indexData.push_back(polyDataStr.substr(0, pos));
        polyDataStr.erase(0, pos + 1);
    }
    indexData.push_back(polyDataStr.substr(0, pos));
    std::cout << "Index data: " << indexData.back() << std::endl;

    for (unsigned int i = 0; i < indexData.size() / typeCount; i++)
    {
        int positionIndex = std::stoi(indexData[i * typeCount]);
        int normalIndex = std::stoi(indexData[i * typeCount + 1]);
        int texCoordIndex = std::stoi(indexData[i * typeCount + 2]);
        processVertex(positionIndex, normalIndex, texCoordIndex);
    }
}

Vertex * GeometryLoader::processVertex(int posIndex, int normIndex, int texIndex)
{
    Vertex * currentVertex = _vertices[posIndex];
    if (!currentVertex->isSet())
    {
        currentVertex->setTextureIndex(texIndex);
        currentVertex->setNormalIndex(normIndex);
        _indices.push_back(posIndex);
        return (currentVertex);
    }
    return (dealWithAlreadyProcessedVertex(currentVertex, texIndex, normIndex));
}

float GeometryLoader::convertDataToArrays()
{
    float furtherstPoint = 0.0;
    for (unsigned int i = 0; i< _vertices.size(); i++)
    {
        Vertex * currentVertex = _vertices[i];
        if (currentVertex->getLength() > furtherstPoint)
            furtherstPoint = currentVertex->getLength();
        glm::vec3 position = currentVertex->getPosition();
        glm::vec2 textureCoord = _textures[currentVertex->getTextureIndex()];
        glm::vec3 normalVector = _normals[currentVertex->getNormalIndex()];
        _verticesArray[i * 3] = position.x;
        _verticesArray[i * 3 + 1] = position.y;
        _verticesArray[i * 3 + 2] = position.z;
        _texturesArray[i * 2] = textureCoord.x;
        _texturesArray[i * 2 + 1] = 1 - textureCoord.y;
        _normalsArray[i * 3] = normalVector.x;
        _normalsArray[i * 3 + 1] = normalVector.y;
        _normalsArray[i * 3 + 2] = normalVector.z;
        VertexSkinData * weights = currentVertex->getWeightsData();
        _jointIDsArray[i * 3] = weights->_jointIDs[0];
        _jointIDsArray[i * 3 + 1] = weights->_jointIDs[1];
        _jointIDsArray[i * 3 + 2] = weights->_jointIDs[2];
        _weightsArray[i * 3] = weights->_weights[0];
        _weightsArray[i * 3 + 1] = weights->_weights[1];
        _weightsArray[i * 3 + 2] = weights->_weights[2];
    }
    return (furtherstPoint);
}


Vertex * GeometryLoader::dealWithAlreadyProcessedVertex(Vertex * previousVertex, int newTextureIndex, int newNormalIndex)
{
    if (previousVertex->hasSameTextureAndNormal(newTextureIndex, newNormalIndex))
    {
        _indices.push_back(previousVertex->getIndex());
        return (previousVertex);
    }
    Vertex * anotherVertex = previousVertex->getDuplicateVertex();
    if (anotherVertex != nullptr)
        return (dealWithAlreadyProcessedVertex(anotherVertex, newTextureIndex, newNormalIndex));
    Vertex * duplicateVertex = new Vertex(_vertices.size(), previousVertex->getPosition(), previousVertex->getWeightsData());
    duplicateVertex->setTextureIndex(newTextureIndex);
    duplicateVertex->setNormalIndex(newNormalIndex);
    previousVertex->setDuplicateVertex(duplicateVertex);
    _vertices.push_back(duplicateVertex);
    _indices.push_back(duplicateVertex->getIndex());
    return (duplicateVertex);
}

void GeometryLoader::initArrays()
{
    this->_verticesArray = std::vector<float>(_vertices.size() * 3, 0.0f);
    this->_texturesArray = std::vector<float>(_vertices.size() * 2, 0.0f);
    this->_normalsArray = std::vector<float>(_vertices.size() * 3, 0.0f);
    this->_jointIDsArray = std::vector<int>(_vertices.size() * 3, 0.0f);
    this->_weightsArray = std::vector<float>(_vertices.size() * 3, 0.0f);
}

//Vertex might need to be a pointer here.
void GeometryLoader::removeUnusedVertices()
{
    for (Vertex * vertex : _vertices)
    {
        vertex->averageTangents();
        if (!vertex->isSet())
        {
            vertex->setTextureIndex(0);
            vertex->setNormalIndex(0);
        }
    }
}
