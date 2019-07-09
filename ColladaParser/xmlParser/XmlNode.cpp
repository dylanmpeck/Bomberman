/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   XmlNode.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpeck <dpeck@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/07 10:45:04 by dpeck             #+#    #+#             */
/*   Updated: 2019/07/07 11:59:13 by dpeck            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "XmlNode.hpp"

XmlNode::XmlNode(std::string name)
{
    this->_name = name;
}

std::string XmlNode::getName()
{
    return (_name);
}

std::string XmlNode::getData()
{
    return (_data);
}

std::string XmlNode::getAttribute(std::string attr)
{
    if (!(_attributes.empty()))
        return (_attributes[attr]);
    return ("");
}

XmlNode * XmlNode::getChild(std::string childName)
{
    if (!_childNodes.empty())
    {
        std::vector<XmlNode *> nodes = _childNodes[childName];
        if (!nodes.empty())
            return (nodes[0]);
    }
    return (nullptr);
}

XmlNode * XmlNode::getChildWithAttributes(std::string childName, std::string attr, std::string value)
{
    std::vector<XmlNode *> children = getChildren(childName);
    if (children.empty())
        return nullptr;
    for (XmlNode * child : children)
    {
        std::string val = child->getAttribute(attr);
        if (value == val)
            return child;
    }
    return nullptr;
}

std::vector<XmlNode *> XmlNode::getChildren(std::string name)
{
    if (!_childNodes.empty())
    {
        std::vector<XmlNode *> children = _childNodes[name];
        if (!children.empty())
            return children;
    }
    return std::vector<XmlNode *>();
}

void XmlNode::addAttribute(std::string attr, std::string value)
{
    _attributes[attr] = value;
}

void XmlNode::addChild(XmlNode * child)
{
    std::vector<XmlNode *> list = _childNodes[child->_name];
    list.push_back(child);
    if (list.size() == 1)
        _childNodes[child->_name] = list;
}

void XmlNode::setData(std::string data)
{
    this->_data = data;
}