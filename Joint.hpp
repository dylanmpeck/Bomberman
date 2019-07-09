/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Joint.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpeck <dpeck@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/04 18:06:37 by dpeck             #+#    #+#             */
/*   Updated: 2019/07/06 11:37:36 by dpeck            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef JOINT_HPP
#define JOINT_HPP

#include <string>
#include <vector>
#include "vendor/glm/glm.hpp"
#include "vendor/glm/gtc/matrix_transform.hpp"

class Joint {

private:
    glm::mat4 _animatedTransform;
    const glm::mat4 _localBindTransform;
    glm::mat4 _inverseBindTransform;

public:
    const int _index; // joint ID
    const std::string _name;
    std::vector<Joint> _children;

    Joint(int index, std::string name, glm::mat4 bindLocalTransform);
    void addChild(Joint child);
    glm::mat4 getAnimatedTransform() const;
    void setAnimationTransform(glm::mat4 animationTransform);
    glm::mat4 getInverseBindTransform() const;
    void calcInverseBindTransform(glm::mat4 parentBindTransform);

};

#endif