/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   GeometryLoader.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpeck <dpeck@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/07 17:13:34 by dpeck             #+#    #+#             */
/*   Updated: 2019/07/07 19:53:15 by dpeck            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "GeometryLoader.hpp"
#include <string>

glm::mat4 GeometryLoader::CORRECTION = glm::rotate(glm::mat4(1.0f), glm::radians(-90.0f), glm::vec3(1.0, 0.0, 0.0));

GeometryLoader::GeometryLoader(XmlNode * geometryNode, std::vector<VertexSkinData> vertexWeights)
{
    this->_vertexWeights = vertexWeights;
    this->_meshData = geometryNode->getChild("geometry")->getChild("mesh");
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
    std::string positionsID = _meshData->getChild("vertices")->getChild("input")->getAttribute("source").substr(1);
    XmlNode * positionsData = _meshData->getChildWithAttributes("source", "id", positionsID)->getChild("float_array");
    int count = std::stoi(positionsData->getAttribute("count"));

    std::string positionsDataStr = positionsData->getData();
    std::vector<std::string> posData;
    size_t pos = 0;
    while ((pos = positionsDataStr.find(" ")) != std::string::npos)
    {
        posData.push_back(positionsDataStr.substr(0, pos));
        positionsDataStr.erase(0, pos + 1);
    }

    for (int i = 0; i < count / 3; i++)
    {
        float x = std::stof(posData[i * 3]);
        float y = std::stof(posData[i * 3 + 1]);
        float z = std::stof(posData[i * 3 + 2]);
        glm::vec4 position(x, y, z, 1.0f);
        position = CORRECTION * position; // transform matrix by vector. might need to be flipped
        _vertices.push_back(Vertex(_vertices.size(), glm::vec3(position.x, position.y, position.z), _vertexWeights[_vertices.size()]));
    }
}

void GeometryLoader::readNormals()
{
    std::string normalsID = _meshData->getChild("polylist")->getChildWithAttributes("input", "semantic", "NORMAL")->getAttribute("source").substr(1);
    XmlNode * normalsData = _meshData->getChildWithAttributes("source", "id", normalsID)->getChild("float_array");
    int count = std::stoi(normalsData->getAttribute("count"));

    std::string normalsDataStr = normalsData->getData();
    std::vector<std::string> normData;
    size_t pos = 0;
    while ((pos = normalsDataStr.find(" ")) != std::string::npos)
    {
        normData.push_back(normalsDataStr.substr(0, pos));
        normalsDataStr.erase(0, pos + 1);
    }

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
    std::string texCoordsID = _meshData->getChild("polylist")->getChildWithAttributes("input", "semantic", "TEXCOORD")->getAttribute("source").substr(1);
    XmlNode * texCoordsData = _meshData->getChildWithAttributes("source", "id", texCoordsID)->getChild("float_array");
    int count = std::stoi(texCoordsData->getAttribute("count"));

    std::string texCoordsDataStr = texCoordsData->getData();
    std::vector<std::string> texData;
    size_t pos = 0;
    while ((pos = texCoordsDataStr.find(" ")) != std::string::npos)
    {
        texData.push_back(texCoordsDataStr.substr(0, pos));
        texCoordsDataStr.erase(0, pos + 1);
    }

    for (int i = 0; i < count / 2; i++)
    {
        float s = std::stof(texData[i * 2]);
        float t = std::stof(texData[i * 2 + 1]);
        _textures.push_back(glm::vec2(s, t));
    }
}

void GeometryLoader::assembleVertices()
{
    XmlNode * poly = _meshData->getChild("polylist");
    int typeCount = poly->getChildren("input").size();

    std::string polyDataStr = poly->getChild("p")->getData();
    std::vector<std::string> indexData;
    size_t pos = 0;
    while ((pos = polyDataStr.find(" ")) != std::string::npos)
    {
        indexData.push_back(polyDataStr.substr(0, pos));
        polyDataStr.erase(0, pos + 1);
    }

    for (unsigned int i = 0; i < indexData.size() / typeCount; i++)
    {
        int positionIndex = std::stoi(indexData[i * typeCount]);
        int normalIndex = std::stoi(indexData[i * typeCount + 1]);
        int texCoordIndex = std::stoi(indexData[i * typeCount + 2]);
        processVertex(positionIndex, normalIndex, texCoordIndex);
    }
}

Vertex GeometryLoader::processVertex(int posIndex, int normIndex, int texIndex)
{
    Vertex * currentVertex = &_vertices[posIndex];
    if (!currentVertex->isSet())
    {
        currentVertex->setTextureIndex(texIndex);
        currentVertex->setNormalIndex(normIndex);
        _indices.push_back(posIndex);
        return (*currentVertex);
    }
    return (dealWithAlreadyProcessedVertex(currentVertex, texIndex, normIndex));
}

float GeometryLoader::convertDataToArrays()
{
    float furtherstPoint = 0.0;
    for (unsigned int i = 0; i< _vertices.size(); i++)
    {
        Vertex currentVertex = _vertices[i];
        if (currentVertex.getLength() > furtherstPoint)
            furtherstPoint = currentVertex.getLength();
        glm::vec3 position = currentVertex.getPosition();
        glm::vec2 textureCoord = _textures[currentVertex.getTextureIndex()];
        glm::vec3 normalVector = _normals[currentVertex.getNormalIndex()];
        _verticesArray[i * 3] = position.x;
        _verticesArray[i * 3 + 1] = position.y;
        _verticesArray[i * 3 + 2] = position.z;
        _texturesArray[i * 2] = textureCoord.x;
        _texturesArray[i * 2 + 1] = 1 - textureCoord.y;
        _normalsArray[i * 3] = normalVector.x;
        _normalsArray[i * 3 + 1] = normalVector.y;
        _normalsArray[i * 3 + 2] = normalVector.z;
        VertexSkinData weights = currentVertex.getWeightsData();
        _jointIDsArray[i * 3] = weights._jointIDs[0];
        _jointIDsArray[i * 3 + 1] = weights._jointIDs[1];
        _jointIDsArray[i * 3 + 2] = weights._jointIDs[2];
        _weightsArray[i * 3] = weights._weights[0];
        _weightsArray[i * 3 + 1] = weights._weights[1];
        _weightsArray[i * 3 + 2] = weights._weights[2];
    }
    return (furtherstPoint);
}


Vertex GeometryLoader::dealWithAlreadyProcessedVertex(Vertex * previousVertex, int newTextureIndex, int newNormalIndex)
{
    if (previousVertex->hasSameTextureAndNormal(newTextureIndex, newNormalIndex))
    {
        _indices.push_back(previousVertex->getIndex());
        return (*previousVertex);
    }
    Vertex * anotherVertex = previousVertex->getDuplicateVertex();
    if (anotherVertex != nullptr)
        return (dealWithAlreadyProcessedVertex(anotherVertex, newTextureIndex, newNormalIndex));
    Vertex * duplicateVertex = new Vertex(_vertices.size(), previousVertex->getPosition(), previousVertex->getWeightsData());
    duplicateVertex->setTextureIndex(newTextureIndex);
    duplicateVertex->setNormalIndex(newNormalIndex);
    previousVertex->setDuplicateVertex(duplicateVertex);
    _vertices.push_back(*duplicateVertex);
    _indices.push_back(duplicateVertex->getIndex());
    return (*duplicateVertex);    
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
    for (Vertex vertex : _vertices)
    {
        vertex.averageTangents();
        if (!vertex.isSet())
        {
            vertex.setTextureIndex(0);
            vertex.setNormalIndex(0);
        }
    }
}
