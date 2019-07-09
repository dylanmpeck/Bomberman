/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   XmlNode.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpeck <dpeck@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/07 10:39:13 by dpeck             #+#    #+#             */
/*   Updated: 2019/07/07 11:13:49 by dpeck            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef XMLNODE_HPP
#define XMLNODE_HPP

#include <string>
#include <unordered_map>
#include <vector>

class XmlNode {

private:
    std::string _name;
    std::unordered_map<std::string, std::string> _attributes;
    std::string _data;
    std::unordered_map<std::string, std::vector<XmlNode *>> _childNodes;

public:
    XmlNode(std::string name);
    std::string getName();
    std::string getData();
    std::string getAttribute(std::string attr);
    XmlNode * getChild(std::string childName);
    XmlNode * getChildWithAttributes(std::string childName, std::string attr, std::string value);
    std::vector<XmlNode *> getChildren(std::string name);
    void addAttribute(std::string attr, std::string value);
    void addChild(XmlNode * child);
    void setData(std::string data);
};

#endif