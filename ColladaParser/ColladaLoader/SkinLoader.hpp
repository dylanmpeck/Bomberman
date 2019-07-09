/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SkinLoader.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpeck <dpeck@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/07 20:25:48 by dpeck             #+#    #+#             */
/*   Updated: 2019/07/08 19:27:45 by dpeck            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SKINLOADER_HPP
#define SKINLOADER_HPP

#include <vector>
#include "DataStructures/SkinningData.hpp"
#include "pugixml/src/pugixml.hpp"

class SkinLoader {

private:
    pugi::xml_node _skinningData;
    int _maxWeights;

public:
    SkinLoader(pugi::xml_node controllersNode, int maxWeights);
    SkinningData extractSkinData();
    std::vector<std::string> loadJointsList();
    std::vector<float> loadWeights();
    std::vector<int> getEffectiveJointsCounts(pugi::xml_node weightsDataNode);
    std::vector<VertexSkinData> getSkinData(pugi::xml_node weightsDataNode, std::vector<int> counts, std::vector<float> weights);
};

#endif