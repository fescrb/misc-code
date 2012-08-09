/* This program is free software. It comes without any warranty, to
 * the extent permitted by applicable law. You can redistribute it
 * and/or modify it under the terms of the Do What The Fuck You Want
 * To Public License, Version 2, as published by Sam Hocevar. See
 * http://sam.zoy.org/wtfpl/COPYING for more details. */

#include "GLUtils.h"

#include "Graphics.h"

#include <cstdio>

void checkGLerror() {
    GLenum error = glGetError();
    if(error != GL_NO_ERROR) {
        switch(error) {
            case GL_INVALID_ENUM:
                printf("GL_INVALID_ENUM\n"); break;
            case GL_INVALID_VALUE:
                printf("GL_INVALID_VALUE\n"); break;
            case GL_INVALID_OPERATION:
                printf("GL_INVALID_OPERATION\n"); break;
            default:
                printf("GlError unknown\n");
        }
    }
}
