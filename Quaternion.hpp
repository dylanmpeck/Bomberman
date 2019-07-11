/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Quaternion.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpeck <dpeck@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/05 20:29:25 by dpeck             #+#    #+#             */
/*   Updated: 2019/07/09 18:53:59 by dpeck            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef QUATERNION_HPP
#define QUATERNION_HPP

#include "vendor/glm/glm.hpp"
#include "vendor/glm/gtc/matrix_transform.hpp"

class Quaternion {

private:
    float x;
    float y;
    float z;
    float w;

public:
    Quaternion();
    Quaternion(float x, float y, float z, float w);
    Quaternion const & operator=(Quaternion const &);
    void normalize();
    glm::mat4 toRotationMatrix() const;
    static Quaternion fromMatrix(glm::mat4 matrix);
    static Quaternion interpolate(Quaternion a, Quaternion b, float blend);
};

#endif