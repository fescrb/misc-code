/* This program is free software. It comes without any warranty, to
 * the extent permitted by applicable law. You can redistribute it
 * and/or modify it under the terms of the Do What The Fuck You Want
 * To Public License, Version 2, as published by Sam Hocevar. See
 * http://sam.zoy.org/wtfpl/COPYING for more details. */

#include "OBJFileReader.h"

#include "MTLFileReader.h"

#include <cstring>
#include <fstream>
#include <cmath>

#include <map>

OBJFileReader::OBJFileReader(const char* filename) {
    m_filename = (char*)malloc(strlen(filename)+1);
    strcpy(m_filename, filename);
}
        
mesh OBJFileReader::getMesh() {
    std::ifstream in;
    in.open(m_filename);
    
    mesh objMesh;
    OBJFileData* data = new OBJFileData;
    // Indexing is different, so we pad.
    data->vertexList.push_back(float4());
    data->normalList.push_back(float4());
    data->textureCoordList.push_back(float4());
    
    int normalCounter = 0;
    
    std::map<std::string,material> materials;
    std::string mtl_filename = std::string(m_filename);
    size_t backslash_loc = mtl_filename.rfind("/");
    if(backslash_loc == mtl_filename.npos)
        backslash_loc = -1;
    
    std::vector<triangle> triangles;
    
    MTLFileReader *mtl_reader;
    
    std::string mtl_in_use;
    
    material cur_material = material();
    
    while(!in.eof()) {
        char line[1024];

        in.getline(line, 1024);
        
        float4 tmp;
        char* filename;
        
        switch(getLineType(line)){
            case TYPE_VERTEX_DECLARATION:
                data->vertexList.push_back(getVertexFromLine(line)); 
                break;
            case TYPE_NORMAL_DECLARATION:
                tmp = getVertexFromLine(line); // tmp = normal
                tmp.setW(0.0f);
                data->normalList.push_back(tmp);
                break;
            case TYPE_TEXTURE_COORD_DECLARATION:
                tmp = getVertexFromLine(line); 
                data->textureCoordList.push_back(tmp);
                break;
            case TYPE_FACE_DECLARATION:
                triangles = getFacesFromLine(line,data,cur_material);
                objMesh.appendTriangles(triangles);
                //objMesh.appendTriangles(getFacesFromLine(line,data,cur_material));
                break;
            case TYPE_MTLLIB_REF:
                strtok(line," ");
                filename = strtok(NULL," \n\0");
                mtl_filename.replace(backslash_loc+1, strlen(filename), filename);
                printf("%s\n",mtl_filename.c_str());
                mtl_reader = new MTLFileReader(mtl_filename.c_str());
                materials = mtl_reader->getMaterials();
                break;
            case TYPE_USEMTL:
                strtok(line," ");
                filename = strtok(NULL," \n\0");
                if(!filename)
                    filename = "";
                mtl_in_use = std::string(filename);
                cur_material = materials[mtl_in_use];
                break;
            default:
                ; // We do nothing.
        }
    }
    
    printf("This model has %d triangles\n", objMesh.getTriangleCount());
    
    return objMesh;
}

OBJFileReader::LineType OBJFileReader::getLineType(const char* line) {
    switch(line[0]) {
        case '#':
            return TYPE_COMMENT;
        case 'v':
            if(line[1] == ' ')
                return TYPE_VERTEX_DECLARATION;
            if(line[1] == 'n')
                return TYPE_NORMAL_DECLARATION;
            if(line[1] == 't')
                return TYPE_TEXTURE_COORD_DECLARATION;
            break;
        case 'f':
            return TYPE_FACE_DECLARATION;
        case 'm':
            if(line[1] == 't' && line[2] == 'l' && line[3] == 'l' && line[4] == 'i' && line[5] == 'b')
                return TYPE_MTLLIB_REF;
        case 'u':
            if(line[1] == 's' && line[2] == 'e' && line[3] == 'm' && line[4] == 't' && line[5] == 'l')
                return TYPE_USEMTL;
        default:
            return TYPE_UNKOWN;
    }
    return TYPE_UNKOWN;
}

float4 OBJFileReader::getVertexFromLine(char* line) {
    strtok(line, " ");
    char* x = strtok(NULL, " ");
    char* y = strtok(NULL, " ");
    char* z = strtok(NULL, " \n\0");
    return float4(atof(x),atof(y),atof(z),1.0f);
}

std::vector<triangle> OBJFileReader::getFacesFromLine(char* line, const OBJFileData* data, material use_mtl) {
    std::vector<triangle> triangles;
    
    int vertex_count = countCharacter(' ', line);
    
    char **all_vertices = (char**) malloc (sizeof(char*)*vertex_count + 1);
    
    strtok(line, " ");
    
    for(int i = 0; i < vertex_count-1; i++) {
        all_vertices[i] = strtok(NULL, " ");
    }
    
    all_vertices[vertex_count-1] = strtok(NULL, " \n\0");
    
    for(int vert = 1; vert < vertex_count - 1; vert++) {
        char* vertices[3] = {all_vertices[0], all_vertices[vert], all_vertices[vert+1]};
        
        int   vertex_indices[3] = {-1, -1, -1};
        int   texture_coord_indices[3] = {-1, -1, -1};
        int   normal_indices[3] = {-1, -1, -1};
        
        // Boolean containing whether we haven't declared a normal.
        bool  undeclared_normal = false;
        bool  has_texture = false;
        
        for(int i = 0; i < 3; i++) {
            int size = strlen(vertices[i]);
            std::string data[] = {std::string(), std::string() ,std::string()};
            int counter = 0; // The amount of '/' we have encountered.
            
            for(int j = 0; j < size; j++) {
                if(vertices[i][j] == '/') {
                    counter++;
                } else {
                    data[counter].push_back(vertices[i][j]);
                }
            }
            
            vertex_indices[i] = atoi(data[0].data());
            if(counter >= 1) {
                if(data[1].size()) {
                    texture_coord_indices[i] = atoi(data[1].data());
                    has_texture = true;
                }
            }
            if(counter == 2)
                normal_indices[i] = atoi(data[2].data());
            else
                undeclared_normal = true;
        }
        
        vertex first(data->vertexList[vertex_indices[0]]);
        vertex secnd(data->vertexList[vertex_indices[1]]);
        vertex third(data->vertexList[vertex_indices[2]]);
        
        
        first.setColour(use_mtl.diffuse);
        secnd.setColour(use_mtl.diffuse);
        third.setColour(use_mtl.diffuse);
        
        if(has_texture && use_mtl.texture) {
            //printf("has texture!! %p\n", use_mtl.texture);
            first.setTexCoord(data->textureCoordList[texture_coord_indices[0]]);
            secnd.setTexCoord(data->textureCoordList[texture_coord_indices[1]]);
            third.setTexCoord(data->textureCoordList[texture_coord_indices[2]]);
        } else {
            //printf("has no texture\n");
            has_texture = false;
        }
        
        triangle new_triangle(first, secnd, third);
        if(has_texture)
            new_triangle.setTexture(use_mtl.texture);
        
        if(undeclared_normal) {
            new_triangle.generateNormals();
        } else {
            new_triangle[0].setNormal(data->normalList[normal_indices[0]]);
            new_triangle[1].setNormal(data->normalList[normal_indices[1]]);
            new_triangle[2].setNormal(data->normalList[normal_indices[2]]);
        }
        
        float4 avg_normal = new_triangle.getAverageNormal();
        //Check for NaN
        if(   new_triangle.getAverageNormal()[0] == new_triangle.getAverageNormal()[0]
           || new_triangle.getAverageNormal()[1] == new_triangle.getAverageNormal()[1]
           || new_triangle.getAverageNormal()[2] == new_triangle.getAverageNormal()[2])
            triangles.push_back(new_triangle);
    }
    
    return triangles;
}

int OBJFileReader::countCharacter(char character, const char* line) {
    int counter = 0;
    int lineSize = strlen(line);
    
    for(int i = 0; i < lineSize; i++)
        if(line[i] == character)
            counter++;
    
    return counter;
}