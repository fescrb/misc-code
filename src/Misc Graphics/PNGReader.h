/* This program is free software. It comes without any warranty, to
 * the extent permitted by applicable law. You can redistribute it
 * and/or modify it under the terms of the Do What The Fuck You Want
 * To Public License, Version 2, as published by Sam Hocevar. See
 * http://sam.zoy.org/wtfpl/COPYING for more details. */

#ifndef MISC_PNG_READER_H
#define MISC_PNG_READER_H

class Texture;

class PNGReader {
    public:
                         PNGReader();
                         PNGReader(const char* filename);
                         PNGReader(const char* folder, const char* filename);
        virtual         ~PNGReader();
        
        Texture         *readImage();
        
    private:
        char            *m_filename;
};

#endif //MISC_PNG_READER_H