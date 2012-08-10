/* This program is free software. It comes without any warranty, to
 * the extent permitted by applicable law. You can redistribute it
 * and/or modify it under the terms of the Do What The Fuck You Want
 * To Public License, Version 2, as published by Sam Hocevar. See
 * http://sam.zoy.org/wtfpl/COPYING for more details. */

#ifndef MISC_RAY_H
#define MISC_RAY_H

#include "Vector.h"
#include "Triangle.h"
#include "Line.h"
#include "Plane.h"

#include<cstdio>

struct ray 
:   public line {
                 ray(float4 o, float4 d) : line(o,d){};
    
    /**
     * Slow method to find the intersection point between a 
     * triangle and a ray.
     * @arg tr The triangle to intersect the ray agains
     * @return The t-value at which the ray intersects the given 
     * triangle. Negative if no intersection
     */        
    float       intersect(triangle tr) {
        float4 v1 = tr.getVertex(0).getPosition();
        float4 v2 = tr.getVertex(1).getPosition();
        float4 v3 = tr.getVertex(2).getPosition();
        
        plane pl = plane(v1, cross(v2-v1, v3-v1));
        
        float t = pl.getIntersectionPoint(*((line*)this));
        
        if (t<0)
            return t;
        
        float4 p = getPositionAt(t);
        
        float4 n1 = normalize(cross(v2-v1,p-v1));
        float4 n2 = normalize(cross(v3-v2,p-v2));
        float4 n3 = normalize(cross(v1-v3,p-v3));
        
        //printf("n1 %f %f %f %f\n", n1.getX(), n1.getY(), n1.getZ(), n1.getW());
        //printf("n2 %f %f %f %f\n", n2.getX(), n2.getY(), n2.getZ(), n2.getW());
        //printf("n3 %f %f %f %f\n", n3.getX(), n3.getY(), n3.getZ(), n3.getW());
        
        if (dot(n1,n2) > 0.0f && dot(n2,n3) > 0.0f) {
            return t;
        } 
        return -1.0f;
    }
};

#endif //MISC_RAY_H