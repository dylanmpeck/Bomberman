/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   JointData.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpeck <dpeck@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/06 15:43:58 by dpeck             #+#    #+#             */
/*   Updated: 2019/07/06 15:45:16 by dpeck            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "JointData.hpp"

JointData::JointData(int index, std::string nameID, glm::mat4 bindLocalTransform) :
 _index(index), _nameID(nameID), _bindLocalTransform(bindLocalTransform)
{

}

void JointData::addChild(JointData child)
{
    _children.push_back(child);
}