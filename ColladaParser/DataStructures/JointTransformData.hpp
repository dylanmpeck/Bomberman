/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   JointTransformData.hpp                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpeck <dpeck@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/06 15:45:25 by dpeck             #+#    #+#             */
/*   Updated: 2019/07/06 15:47:19 by dpeck            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef JOINTTRANSFORMDATA_HPP
#define JOINTTRANSFORMDATA_HPP

#include <string>
#include "vendor/glm/glm.hpp"
#include "vendor/glm/gtc/matrix_transform.hpp"

class JointTransformData {

public:
    std::string _jointNameID;
    glm::mat4 _jointLocalTransform;

    JointTransformData(std::string jointNameID, glm::mat4 jointLocalTransform);
    

};

#endif