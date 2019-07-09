/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   GeometryLoader.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpeck <dpeck@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/07 16:51:27 by dpeck             #+#    #+#             */
/*   Updated: 2019/07/07 19:47:25 by dpeck            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GEOMETRYLOADER_HPP
#define GEOMETRYLOADER_HPP

#include <vector>
#include "vendor/glm/glm.hpp"
#include "vendor/glm/gtc/matrix_transform.hpp"
#include "xmlParser/XmlNode.hpp"
#include "DataStructures/VertexSkinData.hpp"
#include "DataStructures/Vertex.hpp"
#include "DataStructures/MeshData.hpp"

class GeometryLoader {

private:
    static glm::mat4 CORRECTION;
    XmlNode * _meshData;
    std::vector<VertexSkinData> _vertexWeights;

    std::vector<float> _verticesArray;
    std::vector<float> _normalsArray;
    std::vector<float> _texturesArray;
    //std::vector<int> _indicesArray;
    std::vector<int> _jointIDsArray;
    std::vector<float> _weightsArray;

    std::vector<Vertex> _vertices;
    std::vector<glm::vec2> _textures;
    std::vector<glm::vec3> _normals;
    std::vector<int> _indices;

public:
    GeometryLoader(XmlNode * geometryNode, std::vector<VertexSkinData> vertexWeights);
    MeshData extractModelData();

private:
    void readRawData();
    void readPositions();
    void readNormals();
    void readTextureCoords();
    void assembleVertices();
    Vertex processVertex(int posIndex, int normIndex, int texIndex);
    float convertDataToArrays();
    Vertex dealWithAlreadyProcessedVertex(Vertex * previousVertex, int newTextureIndex, int newNormalIndex);
    void initArrays();
    void removeUnusedVertices();
};

#endif