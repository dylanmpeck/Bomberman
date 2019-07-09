/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   JointData.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpeck <dpeck@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/06 15:32:15 by dpeck             #+#    #+#             */
/*   Updated: 2019/07/06 15:40:35 by dpeck            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef JOINTDATA_HPP
#define JOINTDATA_HPP

#include <string>
#include <vector>
#include "vendor/glm/glm.hpp"
#include "vendor/glm/gtc/matrix_transform.hpp"

class JointData {

public:
    int _index;
    std::string _nameID;
    glm::mat4 _bindLocalTransform;
    std::vector<JointData> _children;

    JointData(int index, std::string nameID, glm::mat4 bindLocalTransform);
    void addChild(JointData child);

};

#endif