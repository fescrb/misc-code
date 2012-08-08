/* This program is free software. It comes without any warranty, to
 * the extent permitted by applicable law. You can redistribute it
 * and/or modify it under the terms of the Do What The Fuck You Want
 * To Public License, Version 2, as published by Sam Hocevar. See
 * http://sam.zoy.org/wtfpl/COPYING for more details. */

#ifndef MISC_MATERIAL_H
#define MISC_MATERIAL_H

#include "Vector.h"

#include "Texture.h"

struct material {
                     material() : diffuse(float4(1.0f)), texture(0){}
    float4           diffuse;
    Texture         *texture;
};

#endif //MISC_MATERIAL_H