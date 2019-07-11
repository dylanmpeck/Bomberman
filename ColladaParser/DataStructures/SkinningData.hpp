/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SkinningData.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpeck <dpeck@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/06 16:58:07 by dpeck             #+#    #+#             */
/*   Updated: 2019/07/10 15:38:21 by dpeck            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SKINNINGDATA_HPP
#define SKINNINGDATA_HPP

#include <vector>
#include <string>
#include "VertexSkinData.hpp"

class SkinningData {

public:
    std::vector<std::string> _jointOrder;
    std::vector<VertexSkinData *> _verticesSkinData;

    SkinningData();
    ~SkinningData();
    SkinningData(std::vector<std::string> jointOrder, std::vector<VertexSkinData *> verticesSkinData);
};

#endif