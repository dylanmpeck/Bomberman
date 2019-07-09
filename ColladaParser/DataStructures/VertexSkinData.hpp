/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   VertexSkinData.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpeck <dpeck@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/06 17:33:19 by dpeck             #+#    #+#             */
/*   Updated: 2019/07/06 17:54:42 by dpeck            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VERTEXSKINDATA_HPP
#define VERTEXSKINDATA_HPP

#include <vector>

class VertexSkinData {

public:
    std::vector<int> _jointIDs;
    std::vector<float> _weights;

    void addJointEffect(int jointID, float weight);
    void limitJointNumber(int max);

private:
    void fillEmptyWeights(int max);
    float saveTopWeights(std::vector<float> topWeightsVector);
    void refillWeightList(std::vector<float> topWeights, float total);
    void removeExcessJointIDs(int max);

};

#endif