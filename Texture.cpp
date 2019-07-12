/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Texture.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpeck <dpeck@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/26 18:44:29 by dpeck             #+#    #+#             */
/*   Updated: 2019/07/11 17:02:24 by dpeck            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Texture.hpp"
#include "vendor/stb_image/stb_image.h"
#include <iostream>

Texture::Texture() : _rendererID(-1), _width(0), _height(0), _BPP(0)
{
    return;
}

//TODO make this more modular
//also figure out anisotropic filtering and antialiasing
Texture::Texture(int width, int height, unsigned char *image, GLint internalFormat, GLboolean repeat) : _rendererID(0), _width(width), _height(height)
{
    GLCall(glGenTextures(1, &_rendererID));
    GLCall(glBindTexture(GL_TEXTURE_2D, _rendererID));
    GLCall(glPixelStorei(GL_UNPACK_ALIGNMENT, 1));

    GLCall(glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, width, height, 0, GL_BGRA, GL_UNSIGNED_BYTE, image));

    GLCall(glGenerateMipmap(GL_TEXTURE_2D));

    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR));
    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
    //GLCall(glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_LOD_BIAS, 0));
    GLint param = (repeat) ? GL_REPEAT : GL_CLAMP_TO_EDGE;
    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, param));
    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, param));


    
    GLCall(glBindTexture(GL_TEXTURE_2D, 0));
    //consider adding glGenerateMipmap if textures don't look good
}

Texture::Texture(Texture const & other)
{
    *this = other;
}

Texture const & Texture::operator=(Texture const & rhs)
{
    if (this != &rhs)
    {
        _rendererID = rhs._rendererID;
        _width = rhs._width;
        _height = rhs._height;
        _BPP = rhs._BPP;
    }
    return (*this);
}

Texture::~Texture() 
{
    //GLCall(glDeleteTextures(1, &_rendererID));
}

void Texture::openGLDelete()
{
    GLCall(glDeleteTextures(1, &_rendererID));   
}

void Texture::bind(unsigned slot) const
{
    //predefined slots up to TEXTURE31
    //texture slot = ID - 1
    GLCall(glActiveTexture(GL_TEXTURE0 + slot));
    //might need to be 2D
    GLCall(glBindTexture(GL_TEXTURE_2D, _rendererID));
}

void Texture::unbind() const
{
    GLCall(glBindTexture(GL_TEXTURE_2D, 0));
}

int Texture::getWidth() const
{
    return (_width);
}

int Texture::getHeight() const
{
    return (_height);
}

int Texture::getBPP() const
{
    return (_BPP);
}
