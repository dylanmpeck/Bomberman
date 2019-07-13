/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AnimatedModel.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpeck <dpeck@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/04 18:42:14 by dpeck             #+#    #+#             */
/*   Updated: 2019/07/12 17:41:58 by dpeck            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ANIMATEDMODEL_HPP
#define ANIMATEDMODEL_HPP

#include "VertexArray.hpp"
#include "TextureLoader.hpp"
#include "Animator.hpp"
#include "Animation.hpp"
#include "Joint.hpp"
#include <vector>
#include "vendor/glm/glm.hpp"
#include "vendor/glm/gtc/matrix_transform.hpp"

class Animator;

class AnimatedModel {

private:

    //skin
    VertexArray * _model;
    TextureLoader * _texture;

    //skeleton
    Joint _rootJoint;
    const int _jointCount;

    Animator * _animator;

public:

    AnimatedModel(VertexArray * model, TextureLoader * texture, Joint rootJoint, int jointCount);
    ~AnimatedModel();
    VertexArray * getModel();
    TextureLoader * getTexture();
    Joint getRootJoint();
    void deleteOpenGL(); // shouldn't need this
    void doAnimation(Animation * animation);
    void update();
    const std::vector<glm::mat4> getJointTransforms() const;

private:
    void addJointsToArray(const Joint & headJoint, std::vector<glm::mat4> & jointMatrices) const;

};

#endif