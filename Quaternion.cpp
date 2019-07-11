/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Quaternion.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpeck <dpeck@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/05 20:31:56 by dpeck             #+#    #+#             */
/*   Updated: 2019/07/11 15:44:08 by dpeck            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Quaternion.hpp"
#include <math.h>

Quaternion::Quaternion()
{
    this->x = 0.0f;
    this->y = 0.0f;
    this->z = 0.0f;
    this->w = 0.0f;
}

Quaternion::Quaternion(float x, float y, float z, float w)
{
    this->x = x;
    this->y = y;
    this->z = z;
    this->w = w;
    normalize();
}

Quaternion const & Quaternion::operator=(Quaternion const & rhs)
{
    if (this != &rhs)
    {
        this->x = rhs.x;
        this->y = rhs.y;
        this->z = rhs.z;
        this->w = rhs.w;
    }
    return (*this);
}

void Quaternion::normalize()
{
    float mag = static_cast<float>(sqrtf(w * w + x * x + y * y + z * z));
    w /= mag;
    x /= mag;
    y /= mag;
    z /= mag;
}

glm::mat4 Quaternion::toRotationMatrix() const
{
    glm::mat4 matrix(1.0f);
    const float xy = x * y;
    const float xz = x * z;
    const float xw = x * w;
    const float yz = y * z;
    const float yw = y * w;
    const float zw = z * w;
    const float xSquared = x * x;
    const float ySquared = y * y;
    const float zSquared = z * z;

    matrix[0][0] = 1 - 2 * (ySquared + zSquared);
    matrix[0][1] = 2 * (xy - zw);
    matrix[0][2] = 2 * (xz + yw);
    matrix[0][3] = 0;
    matrix[1][0] = 2 * (xy + zw);
    matrix[1][1] = 1 - 2 * (xSquared + zSquared);
    matrix[1][2] = 2 * (yz - xw);
    matrix[1][3] = 0;
    matrix[2][0] = 2 * (xz - yw);
    matrix[2][1] = 2 * (yz + xw);
    matrix[2][2] = 1 - 2 * (xSquared + ySquared);
    matrix[2][3] = 0;
    matrix[3][0] = 0;
    matrix[3][1] = 0;
    matrix[3][2] = 0;
    matrix[3][3] = 1;
    return matrix;
}

Quaternion Quaternion::fromMatrix(glm::mat4 matrix)
{
    float w, x, y, z;
    float diagonal = matrix[0][0] + matrix[1][1] + matrix[2][2];
    if (diagonal > 0) {
        float w4 = (float) (sqrtf(diagonal + 1.0f) * 2.0f);
        w = w4 / 4.0f;
        x = (matrix[2][1] - matrix[1][2]) / w4;
        y = (matrix[0][2] - matrix[2][0]) / w4;
        z = (matrix[1][0] - matrix[0][1]) / w4;
    } else if ((matrix[0][0] > matrix[1][1]) && (matrix[0][0] > matrix[2][2])) {
        float x4 = (float) (sqrtf(1.0f + matrix[0][0] - matrix[1][1] - matrix[2][2]) * 2.0f);
        w = (matrix[2][1] - matrix[1][2]) / x4;
        x = x4 / 4.0f;
        y = (matrix[0][1] + matrix[1][0]) / x4;
        z = (matrix[0][2] + matrix[2][0]) / x4;
    } else if (matrix[1][1] > matrix[2][2]) {
        float y4 = (float) (sqrtf(1.0f + matrix[1][1] - matrix[0][0] - matrix[2][2]) * 2.0f);
        w = (matrix[0][2] - matrix[2][0]) / y4;
        x = (matrix[0][1] + matrix[1][0]) / y4;
        y = y4 / 4.0f;
        z = (matrix[1][2] + matrix[2][1]) / y4;
    } else {
        float z4 = (float) (sqrtf(1.0f + matrix[2][2] - matrix[0][0] - matrix[1][1]) * 2.0f);
        w = (matrix[1][0] - matrix[0][1]) / z4;
        x = (matrix[0][2] + matrix[2][0]) / z4;
        y = (matrix[1][2] + matrix[2][1]) / z4;
        z = z4 / 4.0f;
    }
    return Quaternion(x, y, z, w);    
}

Quaternion Quaternion::interpolate(Quaternion a, Quaternion b, float blend)
{
    Quaternion result = Quaternion(0, 0, 0, 1);
    float dot = a.w * b.w + a.x * b.x + a.y * b.y + a.z * b.z;
    float blendI = 1.0f - blend;
    if (dot < 0) {
        result.w = blendI * a.w + blend * -b.w;
        result.x = blendI * a.x + blend * -b.x;
        result.y = blendI * a.y + blend * -b.y;
        result.z = blendI * a.z + blend * -b.z;
    } else {
        result.w = blendI * a.w + blend * b.w;
        result.x = blendI * a.x + blend * b.x;
        result.y = blendI * a.y + blend * b.y;
        result.z = blendI * a.z + blend * b.z;
    }
    result.normalize();
    return result;    
}