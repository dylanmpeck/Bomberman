/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MeshData.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpeck <dpeck@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/06 15:50:54 by dpeck             #+#    #+#             */
/*   Updated: 2019/07/10 18:12:58 by dpeck            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MESHDATA_HPP
#define MESHDATA_HPP

#include <vector>

class MeshData {

private:
    static const int DIMENSIONS;

    std::vector<float> _vertices;
    std::vector<float> _textureCoords;
    std::vector<float> _normals;
    std::vector<unsigned int> _indices;
    std::vector<int> _jointIDs;
    std::vector<float> _vertexWeights;

public:
    MeshData(std::vector<float> vertices, std::vector<float> textureCoords, std::vector<float> normals, 
                std::vector<unsigned int> indices, std::vector<int> jointIDs, std::vector<float> vertexWeights);
    std::vector<int> getJointIDs();
    std::vector<float> getVertexWeights();
    std::vector<float> getVertices();
    std::vector<float> getTextureCoords();
    std::vector<float> getNormals();
    std::vector<unsigned int> getIndices();
    int getVertexCount();

};

#endif