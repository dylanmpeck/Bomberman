/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AnimatedModel.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpeck <dpeck@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/04 18:42:14 by dpeck             #+#    #+#             */
/*   Updated: 2019/07/06 15:40:35 by dpeck            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ANIMATEDMODEL_HPP
#define ANIMATEDMODEL_HPP

#include "VertexArray.hpp"
#include "Texture.hpp"
#include "Animator.hpp"
#include <vector>
#include "vendor/glm/glm.hpp"
#include "vendor/glm/gtc/matrix_transform.hpp"

class AnimatedModel {

private:

    //skin
    const VertexArray * _model;
    const Texture * _texture;

    //skeleton
    Joint _rootJoint;
    const int _jointCount;

    Animator * _animator;

public:

    AnimatedModel(VertexArray * model, Texture * texture, Joint rootJoint, int jointCount);
    ~AnimatedModel();
    const VertexArray * getModel();
    const Texture * getTexture();
    Joint getRootJoint();
    void deleteOpenGL(); // shouldn't need this
    void doAnimation(Animation * animation);
    void update();
    std::vector<glm::mat4> getJointTransforms();

private:
    void addJointsToArray(const Joint & headJoint, std::vector<glm::mat4> & jointMatrices);

};

#endif