/* This program is free software. It comes without any warranty, to
 * the extent permitted by applicable law. You can redistribute it
 * and/or modify it under the terms of the Do What The Fuck You Want
 * To Public License, Version 2, as published by Sam Hocevar. See
 * http://sam.zoy.org/wtfpl/COPYING for more details. */

#ifndef MISC_MESH_H
#define MISC_MESH_H

#include "Triangle.h"

#include <vector>

struct mesh {
    public:
                                         mesh():m_triangles(){};
                                         mesh(const mesh& other)
                                         :  m_triangles(other.m_triangles){};

        inline void                      appendTriangle(const triangle& triangl) {
            m_triangles.push_back(triangl);
        }

        inline void                      appendTriangles(const std::vector<triangle>& triangles) {
            m_triangles.insert(m_triangles.end(), triangles.begin(), triangles.end());
        }

        inline triangle                  getTriangle(const int& index)  const{
            return m_triangles[index];
        }

        inline int                       getTriangleCount() const {
            return m_triangles.size();
        }

        inline std::vector<triangle>&    getTriangleList() {
            return m_triangles;
        }

        inline void                      setTriangle(const int& index, const triangle& triangl) {
            operator[](index) = triangl;
        }

        inline void                      removeTriangle(const int& index) {
            m_triangles.erase(m_triangles.begin()+index);
        }

        inline triangle&                 operator[](const int& index){
            return m_triangles[index];
        }
        
        inline mesh&                     operator=(const mesh& other) {
            if(this != &other) {
                this->m_triangles.clear();
                for(int i = 0; i < other.getTriangleCount(); i++) 
                    this->m_triangles.push_back(other.getTriangle(i));
            }
            return *this;
        }

        //inline mesh&                 operator*(const );

        /**
         * Returns the 6 outermost vertices that bound the volume in the
         * x positive and negative directions as well as the y and z.
         * @return The outermost vertices in the following order: {x+, x-, y+, y-, z+. z-}
         */
        std::vector<vertex>              getOuterMostVertices() const;

        void                             render() const;

    private:
        std::vector<triangle>            m_triangles;
};

#endif //MISC_MESH_H
