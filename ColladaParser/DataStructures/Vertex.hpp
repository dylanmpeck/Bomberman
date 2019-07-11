/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Vertex.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpeck <dpeck@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/06 17:00:46 by dpeck             #+#    #+#             */
/*   Updated: 2019/07/10 15:37:01 by dpeck            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VERTEX_HPP
#define VERTEX_HPP

#include <vector>
#include "vendor/glm/glm.hpp"
#include "vendor/glm/gtc/matrix_transform.hpp"
#include "VertexSkinData.hpp"

class Vertex {

private:
    static const int NO_INDEX;

    glm::vec3 _position;
    int _textureIndex;
    int _normalIndex;
    Vertex * _duplicateVertex;
    int _index;
    float _length;
    std::vector<glm::vec3> _tangents;
    glm::vec3 _averagedTangent;

    VertexSkinData * _weightsData;

public:
    ~Vertex();
    Vertex(Vertex const &);
    Vertex const & operator=(Vertex const &);
    Vertex(int index, glm::vec3 position, VertexSkinData * weightsData);
    VertexSkinData * getWeightsData();
    void addTangent(glm::vec3 tangent);
    void averageTangents();
    glm::vec3 getAverageTangent();
    int getIndex();
    float getLength();
    bool isSet();
    bool hasSameTextureAndNormal(int textureIndexOther, int normalIndexOther);
    void setTextureIndex(int textureIndex);
    void setNormalIndex(int normalIndex);
    glm::vec3 getPosition();
    int getTextureIndex();
    int getNormalIndex();
    Vertex * getDuplicateVertex();
    void setDuplicateVertex(Vertex * duplicateVertex);
};

#endif