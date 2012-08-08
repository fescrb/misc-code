/* This program is free software. It comes without any warranty, to
 * the extent permitted by applicable law. You can redistribute it
 * and/or modify it under the terms of the Do What The Fuck You Want
 * To Public License, Version 2, as published by Sam Hocevar. See
 * http://sam.zoy.org/wtfpl/COPYING for more details. */

#ifndef MISC_MATH_UTIL_H
#define MISC_MATH_UTIL_H

inline unsigned char float_to_8_bit_unsigned_fixed_point(float to_convert) {
    double range =255.0f; // Max value of a 8 bit unsigned integer.
    double step = 1.0f/range;
    return to_convert/step;
}

inline float unsigned_8bit_fixed_point_to_float(unsigned char to_convert) {
    double range =255.0f; // Max value of a 8 bit unsigned integer.
    double step = 1.0f/range;
    return to_convert*step;
}

inline float fixed_point_8bit_to_float(char to_convert) {
    double range =128.0f; // Max value of a 7 bit unsigned integer.
    double step = 1.0f/range;
    return to_convert*step;
}

inline char float_to_fixed_point_8bit(float to_convert) {
    double range =127.0f; // Max value of a 7 bit unsigned integer.
    double step = 1.0f/range;
    return to_convert/step;
}

#endif //MISC_MATH_UTIL_H