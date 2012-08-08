/* This program is free software. It comes without any warranty, to
 * the extent permitted by applicable law. You can redistribute it
 * and/or modify it under the terms of the Do What The Fuck You Want
 * To Public License, Version 2, as published by Sam Hocevar. See
 * http://sam.zoy.org/wtfpl/COPYING for more details. */

#ifndef MISC_HIGH_RES_TIMER_H
#define MISC_HIGH_RES_TIMER_H

struct high_res_timer {
    public:
                         high_res_timer();
        void             reset();
        
        inline high_res_timer 
                         operator+ (const high_res_timer rhs) {
            high_res_timer timer;
            timer.m_seconds = m_seconds + rhs.m_seconds;
            return timer;
        }
        
        inline high_res_timer 
                         operator-(const high_res_timer rhs) {
            high_res_timer timer;
            timer.m_seconds = m_seconds -rhs.m_seconds;
            return timer;
        }
        
        inline operator  double() {
            return m_seconds;
        }
        
    private:
        
        double            m_seconds;
};

#endif //MISC_HIGH_RES_TIMER_H