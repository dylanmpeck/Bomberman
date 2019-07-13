/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   TextureLoader.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpeck <dpeck@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/26 18:40:46 by dpeck             #+#    #+#             */
/*   Updated: 2019/05/31 16:09:21 by dpeck            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TextureLoader_HPP
#define TextureLoader_HPP

#include "GLDebug.hpp"
#include "glad/glad.h"

class TextureLoader {

private:
    unsigned int _rendererID;
    int _width, _height, _BPP;

public:
    TextureLoader();
    TextureLoader(int width, int height, unsigned char *image, int nbrComponents);
    TextureLoader(TextureLoader const &);
    TextureLoader const & operator=(TextureLoader const &);
    ~TextureLoader();

    void bind(unsigned int slot = 0) const;
    void unbind() const;

    void openGLDelete();

    int getWidth() const;
    int getHeight() const;
    int getBPP() const;
    unsigned int getID();
};

#endif
