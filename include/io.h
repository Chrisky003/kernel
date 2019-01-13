#pragma once
#include "types.h"

namespace io {
    namespace port {
        void out8(uint16 port, uint8 value);
        uint8 in8(uint16 port);
        uint16 in16(uint16 port);
    }
    namespace console {
        namespace real {
            enum color {
                black = 0,
                blue = 1,
                green = 2,
                cyan = 3,
                red = 4,
                magenta = 5,
                brown = 6,
                light_grey = 7,
                dark_grey = 8,
                light_blue = 9,
                light_green = 10,
                light_cyan = 11,
                light_red = 12,
                light_magenta = 13,
                light_brown  = 14, 	// yellow
                yellow = light_brown,
                white = 15
            };
            void clear();
            void move_cursor(int x, int y);
            void move_cursor(POINT p);
            void putc(char c, color back = color::black, \
                color fore = color::white);
            void puts(char str[], color back = color::black, \
                color fore = color::white);
            void printk(const char *format, ...);
            void printk_color(color back, color fore, const char *format, ...);
        }
        namespace real_console = real;
    }
}