/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   TextureLoader.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpeck <dpeck@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/26 18:44:29 by dpeck             #+#    #+#             */
/*   Updated: 2019/07/11 17:02:24 by dpeck            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "TextureLoader.hpp"
#include "vendor/stb_image/stb_image.h"
#include <iostream>

TextureLoader::TextureLoader() : _rendererID(-1), _width(0), _height(0), _BPP(0)
{
    return;
}

//TODO make this more modular
//also figure out anisotropic filtering and antialiasing
TextureLoader::TextureLoader(int width, int height, unsigned char *image, int nbrComponents) : _rendererID(0), _width(width), _height(height)
{
    GLCall(glGenTextures(1, &_rendererID));

    if (image)
    {
        GLenum format;
        if (nbrComponents == 1)
            format = GL_RED;
        else if (nbrComponents == 3)
            format = GL_RGB;
        else if (nbrComponents == 4)
            format = GL_RGBA;
        
        GLCall(glBindTexture(GL_TEXTURE_2D, _rendererID));
        GLCall(glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, image));
        GLCall(glGenerateMipmap(GL_TEXTURE_2D));

        GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT));
        GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT));
        GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR));
        GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
    }
    else
        std::cout << "Texture failed to load at path: " << std::endl;
}

TextureLoader::TextureLoader(TextureLoader const & other)
{
    *this = other;
}

TextureLoader const & TextureLoader::operator=(TextureLoader const & rhs)
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

TextureLoader::~TextureLoader() 
{
    //GLCall(glDeleteTextures(1, &_rendererID));
}

void TextureLoader::openGLDelete()
{
    GLCall(glDeleteTextures(1, &_rendererID));   
}

void TextureLoader::bind(unsigned slot) const
{
    //predefined slots up to TEXTURE31
    //texture slot = ID - 1
    GLCall(glActiveTexture(GL_TEXTURE0 + slot));
    //might need to be 2D
    GLCall(glBindTexture(GL_TEXTURE_2D, _rendererID));
}

void TextureLoader::unbind() const
{
    GLCall(glBindTexture(GL_TEXTURE_2D, 0));
}

int TextureLoader::getWidth() const
{
    return (_width);
}

int TextureLoader::getHeight() const
{
    return (_height);
}

int TextureLoader::getBPP() const
{
    return (_BPP);
}

unsigned int TextureLoader::getID()
{
    return (_rendererID);
}
