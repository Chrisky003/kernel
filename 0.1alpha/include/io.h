#pragma once
#include "def.h"

namespace io
{
	namespace memory
	{
		byte in8(dword _where);
		void out8(dword _where, byte data);
		word in16(dword _where);
		void out16(dword _where, word data);
		dword in32(dword _where);
		void out32(dword _where, dword data);
		dword copy(void *dest, const void *src, int size);
		void set(void *src, byte data, int size);
		void zero(void *src, int size);
		int *intToPointer(int i);
		int pointerToInt(void *p);
	}
	
	namespace port
	{
		void out8(word port, byte value);
		byte in8(word port);
		short in16(word port);
	}

	namespace console
	{
		namespace real
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
			void print_color(color back, color fore, const char *format, ...);
		}

		// namespace virtual
		// {
		// 	//TODO: 虚拟终端
		// }
	}

	//TODO: 移动到容器
    namespace string
    {
        int strlen(const char *str);
        int strcpy(char *dest, const char *src);
        int strcmp(const char *str1, const char *str2);
    }
}
