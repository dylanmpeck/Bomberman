/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   JointTransform.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpeck <dpeck@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/05 20:14:37 by dpeck             #+#    #+#             */
/*   Updated: 2019/07/05 20:45:46 by dpeck            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef JOINTTRANSFORM_HPP
#define JOINTTRANSFORM_HPP

#include "vendor/glm/glm.hpp"
#include "vendor/glm/gtc/matrix_transform.hpp"
#include "Quaternion.hpp"

class JointTransform {

private:
    const glm::vec3 _position;
    const Quaternion _rotation;

public:
    JointTransform(glm::vec3 position, Quaternion rotation);
    glm::mat4 getLocalTransform();
    static JointTransform interpolate(JointTransform frameA, JointTransform frameB, float progression);

private:
    static glm::vec3 interpolate(glm::vec3 start, glm::vec3 end, float progression);

};

#endif