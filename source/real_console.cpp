#include "real_console.h"
#include "port.h"
#include "memory.h"
#include "string.h"

namespace real_console
{
	const int width = 80;
	const int height = 25;

	POINT cursorPos;

	POINT getCursorPos()
	{
		return cursorPos;
	}

	void setCursorPos(::POINT p)
	{
		if (!(p.x < 0 || p.x >= width))
			cursorPos.x = p.x;
		if (!(p.y < 0 || p.y >= height))
			cursorPos.y = p.y;
		word location = cursorPos.y * width + cursorPos.x;
		port::out8(0x3d4, 14);
		port::out8(0x3d5, location >> 8);
		port::out8(0x3d4, 15);
		port::out8(0x3d5, location & 0xff);
	}
	
	void setCursorPos(const int x, const int y)
	{
		
		if (!(x < 0 || x >= width))
			cursorPos.x = x;
		if (!(y < 0 || y >= height))
			cursorPos.y = y;
		word location = cursorPos.y * width + cursorPos.x;
		port::out8(0x3d4, 14);
		port::out8(0x3d5, location >> 8);
		port::out8(0x3d4, 15);
		port::out8(0x3d5, location & 0xff);
	}


	void clear()
	{
		for (int i = 0; i < width * height; i++)
		{
			memory::write16(0xb8000, ' ' | \
			(word)((color::black << 4) | (color::white & 0x0F)) << 8);
		}
		setCursorPos(0, 0);
	}
		
	void putc(const char c, const color back, const color fore)
	{
		byte bc(back), fc(fore);
		POINT curpos(getCursorPos());
		if (c == 0x08 && curpos.x) 
		{
			curpos.x--;;
		} 
		else if (c == 0x09) 
		{
			curpos.x = (curpos.x + 8) & ~(8 - 1);
		} 
		else if (c == '\r') 
		{
			curpos.x = 0;
		} 
		else if (c == '\n') 
		{
			curpos.x = 0;
			curpos.y++;
		} 
		else if (c >= ' ') 
		{
			memory::write16(0xb8000 + (curpos.y * 80 + curpos.x) * 2, c | \
				(word)((bc << 4) | (fc & 0x0F)) << 8);
			curpos.x++;
		}
		
		if (curpos.x >= width)
		{
			curpos.x = 0;
			curpos.y ++;
		}
		
		if (curpos.y >= height) 
		{
			union{char* p; int data;} uni, uni2;
			uni.data = 0xb8000;
			uni2.data = 0xb8000 + 1 * width * 2;
			memory::memcpy(uni.p, uni2.p, width * (height - 1) * 2);
			uni2.data = 0xb8000 + (height - 1) * width * 2;
			memory::memset(uni2.p, (char)'\0', width * 1 * 2);
			curpos.y = height - 1;
		}
		setCursorPos(curpos);
	}
	
	void puts(const char *str, const color back, const color fore)
	{
		for(int i = 0; str[i] != 0; i++)
		{
			putc(str[i], back, fore);
		}
	}
		
	static int vsprintf(char *buff, const char *format, va_list args);

	void printk(const char *format, ...)
	{
		// 避免频繁创建临时变量，内核的栈很宝贵
		static char buff[1024];
		va_list args;
		int i;

		va_start(args, format);
		i = vsprintf(buff, format, args);
		va_end(args);

		buff[i] = '\0';

		real_console::puts(buff);
	}

	void printk_color(real_console::color back, \
		real_console::color fore, const char *format, ...)
	{
		// 避免频繁创建临时变量，内核的栈很宝贵
		static char buff[1024];
		va_list args;
		int i;

		va_start(args, format);
		i = vsprintf(buff, format, args);
		va_end(args);

		buff[i] = '\0';

		puts(buff, back, fore);
	}

	#define is_digit(c)	((c) >= '0' && (c) <= '9')

	static int skip_atoi(const char **s)
	{
		int i = 0;

		while (is_digit(**s)) {
			i = i * 10 + *((*s)++) - '0';
		}

		return i;
	}

	#define ZEROPAD		1	// pad with zero
	#define SIGN	 	2   	// unsigned/signed long
	#define PLUS    	4	// show plus
	#define SPACE	  	8   	// space if plus
	#define LEFT	 	16  	// left justified
	#define SPECIAL		32  	// 0x
	#define SMALL	  	64  	// use 'abcdef' instead of 'ABCDEF'

	#define do_div(n,base) ({ \
			int __res; \
			__asm__("divl %4":"=a" (n),"=d" (__res):"0" (n),"1" (0),"r" (base)); \
			__res; })

	static char *number(char *str, int num, int base, int size, int precision, int type)
	{
		char c, sign, tmp[36];
		const char *digits = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
		int i;

		if (type & SMALL) {
			digits ="0123456789abcdefghijklmnopqrstuvwxyz";
		}
		if (type & LEFT) {
			type &= ~ZEROPAD;
		}
		if (base < 2 || base > 36) {
			return 0;
		}

		c = (type & ZEROPAD) ? '0' : ' ' ;

		if (type & SIGN && num < 0) {
			sign = '-';
			num = -num;
		} else {
			sign = (type&PLUS) ? '+' : ((type&SPACE) ? ' ' : 0);
		}

		if (sign) {
			  size--;
		}
		if (type & SPECIAL) {
			if (base == 16) {
				size -= 2;
			} else if (base == 8) {
				size--;
			}
		}
		i = 0;
		if (num == 0) {
			tmp[i++] = '0';
		} else {
			while (num != 0) {
				tmp[i++] = digits[do_div(num,base)];
			}
		}

		if (i > precision) {
			precision = i;
		}
		size -= precision;

		if (!(type&(ZEROPAD+LEFT))) {
			while (size-- > 0) {
				*str++ = ' ';
			}
		}
		if (sign) {
			*str++ = sign;
		}
		if (type & SPECIAL) {
			if (base == 8) {
				*str++ = '0';
			} else if (base == 16) {
				*str++ = '0';
				*str++ = digits[33];
			}
		}
		if (!(type&LEFT)) {
			while (size-- > 0) {
				*str++ = c;
			}
		}
		while (i < precision--) {
			*str++ = '0';
		}
		while (i-- > 0) {
			*str++ = tmp[i];
		}
		while (size-- > 0) {
			*str++ = ' ';
		}

		return str;
	}

	static int vsprintf(char *buff, const char *format, va_list args)
	{
		int len;
		int i;
		char *str;
		char *s;
		int *ip;

		int flags;		// flags to number()

		int field_width;	// width of output field
		int precision;		// min. # of digits for integers; max number of chars for from string

		for (str = buff ; *format ; ++format) {
			if (*format != '%') {
				*str++ = *format;
				continue;
			}
				
			flags = 0;
			repeat:
				++format;		// this also skips first '%'
				switch (*format) {
					case '-': flags |= LEFT;
						  goto repeat;
					case '+': flags |= PLUS;
						  goto repeat;
					case ' ': flags |= SPACE;
						  goto repeat;
					case '#': flags |= SPECIAL;
						  goto repeat;
					case '0': flags |= ZEROPAD;
						  goto repeat;
				}
			
			// get field width
			field_width = -1;
			if (is_digit(*format)) {
				field_width = skip_atoi(&format);
			} else if (*format == '*') {
				// it's the next argument
				field_width = va_arg(args, int);
				if (field_width < 0) {
					field_width = -field_width;
					flags |= LEFT;
				}
			}

			// get the precision
			precision = -1;
			if (*format == '.') {
				++format;	
				if (is_digit(*format)) {
					precision = skip_atoi(&format);
				} else if (*format == '*') {
					// it's the next argument
					precision = va_arg(args, int);
				}
				if (precision < 0) {
					precision = 0;
				}
			}

			// get the conversion qualifier
			//int qualifier = -1;	// 'h', 'l', or 'L' for integer fields
			if (*format == 'h' || *format == 'l' || *format == 'L') {
				//qualifier = *format;
				++format;
			}

			switch (*format) {
			case 'c':
				if (!(flags & LEFT)) {
					while (--field_width > 0) {
						*str++ = ' ';
					}
				}
				*str++ = (unsigned char) va_arg(args, int);
				while (--field_width > 0) {
					*str++ = ' ';
				}
				break;

			case 's':
				s = va_arg(args, char *);
				len = string::strlen(s);
				if (precision < 0) {
					precision = len;
				} else if (len > precision) {
					len = precision;
				}

				if (!(flags & LEFT)) {
					while (len < field_width--) {
						*str++ = ' ';
					}
				}
				for (i = 0; i < len; ++i) {
					*str++ = *s++;
				}
				while (len < field_width--) {
					*str++ = ' ';
				}
				break;

			case 'o':
				str = number(str, va_arg(args, unsigned long), 8,
					field_width, precision, flags);
				break;

			case 'p':
				if (field_width == -1) {
					field_width = 8;
					flags |= ZEROPAD;
				}
				str = number(str, (unsigned long) va_arg(args, void *), 16,
					field_width, precision, flags);
				break;

			case 'x':
				flags |= SMALL;
			case 'X':
				str = number(str, va_arg(args, unsigned long), 16,
					field_width, precision, flags);
				break;

			case 'd':
			case 'i':
				flags |= SIGN;
			case 'u':
				str = number(str, va_arg(args, unsigned long), 10,
					field_width, precision, flags);
				break;
			case 'b':
				str = number(str, va_arg(args, unsigned long), 2,
					field_width, precision, flags);
				break;

			case 'n':
				ip = va_arg(args, int *);
				*ip = (str - buff);
				break;

			default:
				if (*format != '%')
					*str++ = '%';
				if (*format) {
					*str++ = *format;
				} else {
					--format;
				}
				break;
			}
		}
		*str = '\0';

		return (str -buff);
	}


}



