#pragma once
#include "def.h"

namespace real_console
{
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
		light_brown = 14,
		white = 15};
	void clear();
	POINT getCursorPos();
	void setCursorPos(POINT p);
	void setCursorPos(const int x, const int y);
	void scroll();
	void putc(const char c, const color back = color::black, const color fore = color::white);
	void puts(const char *str, const color back = color::black, const color fore = color::white);
	void print(const char *format, ...);
	void print_color(real_console::color back, real_console::color fore, const char *format, ...);
}
