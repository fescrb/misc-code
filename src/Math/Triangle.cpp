/* This program is free software. It comes without any warranty, to
 * the extent permitted by applicable law. You can redistribute it
 * and/or modify it under the terms of the Do What The Fuck You Want
 * To Public License, Version 2, as published by Sam Hocevar. See
 * http://sam.zoy.org/wtfpl/COPYING for more details. */

#include "Triangle.h"

#include "Graphics.h"

void triangle::render() const {
    
    GLuint text = 0;
    
    if(m_texture)
        text = m_texture->getGLTexture();
    
    glBindTexture(GL_TEXTURE_2D, text);
    glBegin(GL_TRIANGLES);
    for(int j = 0; j < 3; j++) {
        vertex this_vertex = getVertex(j);
        float4 colour = this_vertex.getColour();
        float4 normal = this_vertex.getNormal();
        float4 position = this_vertex.getPosition();
        float2 textCoord = this_vertex.getTexCoord();
        glColor4f(colour.getX(), colour.getY(), colour.getZ(), colour.getW());
        glNormal3f(normal.getX(), normal.getY(), normal.getZ());
        glTexCoord2f(textCoord.getX(), textCoord.getY());
        glVertex4f(position.getX(), position.getY(), position.getZ(), position.getW());
    }
    glEnd();
}
