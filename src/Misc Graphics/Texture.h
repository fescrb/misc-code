/* This program is free software. It comes without any warranty, to
 * the extent permitted by applicable law. You can redistribute it
 * and/or modify it under the terms of the Do What The Fuck You Want
 * To Public License, Version 2, as published by Sam Hocevar. See
 * http://sam.zoy.org/wtfpl/COPYING for more details. */

#ifndef MISC_TEXTURE_H
#define MISC_TEXTURE_H

#include "Graphics.h"

#include "Image.h"

#include "Vector.h"

class Texture
:   public Image {
    public:
                         Texture(unsigned int width, 
                                 unsigned int height, 
                                 ImageFormat buffer_format, 
                                 const char* buffer);
        virtual         ~Texture();
        
        GLuint           getGLTexture();
        
        float4           getColourAt(float2 coordinates) const;
        
    private:
        void             transferToGL();
        
        GLuint           m_texture;
};

#endif //MISC_TEXTURE_H