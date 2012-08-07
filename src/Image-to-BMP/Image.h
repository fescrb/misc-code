/* This program is free software. It comes without any warranty, to
 * the extent permitted by applicable law. You can redistribute it
 * and/or modify it under the terms of the Do What The Fuck You Want
 * To Public License, Version 2, as published by Sam Hocevar. See
 * http://sam.zoy.org/wtfpl/COPYING for more details. */

#ifndef MISC_IMAGE_H
#define MISC_IMAGE_H

class Image {
    public:
        enum ImageFormat {
            RGB,
            RGBA
        };
    
        explicit          Image(unsigned int width, unsigned int height);
        explicit          Image(unsigned int width, 
                                unsigned int height, 
                                ImageFormat buffer_format, 
                                const char* buffer);
        explicit          Image(Image* image);
        
        void              toBMP(const char* filename);
        
    protected:
        unsigned int      m_width;
        unsigned int      m_height;
        char             *m_pData;
};

#endif //MISC_IMAGE_H
