/* This program is free software. It comes without any warranty, to
 * the extent permitted by applicable law. You can redistribute it
 * and/or modify it under the terms of the Do What The Fuck You Want
 * To Public License, Version 2, as published by Sam Hocevar. See
 * http://sam.zoy.org/wtfpl/COPYING for more details. */

#ifndef MISC_OBJ_FILE_READER_H
#define MISC_OBJ_FILE_READER_H

#include "Mesh.h"

#include "Material.h"

class OBJFileReader {
    public:
        explicit                 OBJFileReader(const char* filename);
        
        enum                     LineType {
            TYPE_COMMENT, 
            TYPE_VERTEX_DECLARATION,
            TYPE_NORMAL_DECLARATION,
            TYPE_TEXTURE_COORD_DECLARATION,
            TYPE_FACE_DECLARATION,
            TYPE_MTLLIB_REF,
            TYPE_USEMTL,
            TYPE_UNKOWN
        };
        
        struct                   OBJFileData {
            std::vector<float4>  vertexList;
            std::vector<float4>  normalList;
            std::vector<float4>  textureCoordList;
        };
        
        mesh                     getMesh();
     
    private:
        LineType                 getLineType(const char* line);
        
        float4                   getVertexFromLine(char* line);
        
        /**
         * Processes the given string and creates all the triangles it describes.
         * If more than 1 triangle is defined they are treated as a triangle fan.
         * @param line The string containing face data.
         * @param data A pointer to the current obj file status.
         * @return A list of all the triangles defined in the line.
         */
        std::vector<triangle>    getFacesFromLine(char* line, const OBJFileData* data, material use_mtl);
        
        int                      countCharacter(char character, const char* line);
        
        char*                    m_filename;
};

#endif //MISC_OBJ_FILE_READER_H