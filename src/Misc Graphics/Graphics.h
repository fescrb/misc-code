/* This program is free software. It comes without any warranty, to
 * the extent permitted by applicable law. You can redistribute it
 * and/or modify it under the terms of the Do What The Fuck You Want
 * To Public License, Version 2, as published by Sam Hocevar. See
 * http://sam.zoy.org/wtfpl/COPYING for more details. */

#ifndef MISC_GRAPHICS_H
#define MISC_GRAPHICS_H

#ifdef _LINUX
    #include <GL/glut.h>
    #include <GL/gl.h>
    #include <GL/glext.h>
    #include <GL/glx.h>
#endif //_LINUX

#ifdef _OSX
    #include <glut.h>
    #include <OpenGL/gl.h>
    #include <OpenGL/glext.h>
#endif //_OSX

#endif //MISC_GRAPHICS_H
