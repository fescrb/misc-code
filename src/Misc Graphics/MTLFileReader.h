/* This program is free software. It comes without any warranty, to
 * the extent permitted by applicable law. You can redistribute it
 * and/or modify it under the terms of the Do What The Fuck You Want
 * To Public License, Version 2, as published by Sam Hocevar. See
 * http://sam.zoy.org/wtfpl/COPYING for more details. */

#ifndef MISC_MTL_FILE_READER_H
#define MISC_MTL_FILE_READER_H

#include <map>
#include <string>

#include "Vector.h"

#include "Material.h"

class MTLFileReader {
    public:
        explicit                         MTLFileReader(const char* filename);
        
        enum                     LineType {
            TYPE_NEWMTL, 
            TYPE_KD,
            TYPE_KD_TEXTURE,
            TYPE_UNKOWN
        };
        
        std::map<std::string,material>   getMaterials();
     
    private:
        LineType                         getLineType(const char* line);
        
        char*                            m_filename;
};

#endif //MISC_MTL_FILE_READER_H