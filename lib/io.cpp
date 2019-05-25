#include "stdlib.h"

namespace io{
	namespace port {
		// 端口写一个字节
		inline void out8(uint16 port, uint8 value) {
			asm volatile ("outb %1, %0" : : "dN" (port), "a" (value));
		}
		// 端口读一个字节
		inline uint8 in8(uint16 port) {
			uint8 ret;
			asm volatile("inb %1, %0" : "=a" (ret) : "dN" (port));
			return ret;
		}
		// 端口写一个字
		inline void out16(uint16 port, uint16 value) {
			asm volatile ("outw %1, %0" : : "dN" (port), "a" (value));
		}
		// 端口读一个字
		inline uint16 in16(uint16 port) {
			uint16 ret;
			asm volatile ("inw %1, %0" : "=a" (ret) : "dN" (port));
			return ret;
		}
	}
	namespace console {
		namespace real {
			uint16 *videoMem = ((uint16 *)(0xb8000));
			// enum color {
			// 	black = 0,
			// 	blue = 1,
			// 	green = 2,
			// 	cyan = 3,
			// 	red = 4,
			// 	magenta = 5,
			// 	brown = 6,
			// 	light_grey = 7,
			// 	dark_grey = 8,
			// 	light_blue = 9,
			// 	light_green = 10,
			// 	light_cyan = 11,
			// 	light_red = 12,
			// 	light_magenta = 13,
			// 	light_brown  = 14, 	// yellow
			// 	yellow = light_brown,
			// 	white = 15
			// };
			int x(0), y(0);
			void clear() {
				uint16 blank = 0x20 | (((0 << 4) | (15 & 0x0f)) << 8);
				for (int i = 0; i < 80 * 25; i++) {
					((uint16 *)(0xb8000))[i] = blank;
				}
				move_cursor(0, 0);
			}
			void move_cursor(int x, int y) {
				if (x == -1)
					x = real::x;
				if (y == -1)
					y = real::y;
				uint16 location = y * 80 + x;
				port::out8(0x3D4, 14);
				port::out8(0x3D5, location >> 8);
				port::out8(0x3D4, 15);
				port::out8(0x3D5, location & 0xff);
				real::x = x;
				real::y = y;
			}
			void move_cursor(POINT p) {
				move_cursor(p.x, p.y);
			}
			void putc_nomove(char c, color back, color fore, POINT &p) {
				uint16 attribute = ((back << 4) | (fore & 0x0F)) << 8;

				//POINT p(x, y);
				// 0x08 是 退格键 的 ASCII 码
				// 0x09 是 tab 键 的 ASCII 码
				if (c == 0x08 && x) {
					p.x--;
				} else if (c == 0x09) {
					p.x = (p.x + 8) & ~(8 - 1);
				} else if (c == '\r') {
					p.x = 0;
				} else if (c == '\n') {
					p.x = 0;
					p.y++;
				} else if (c >= ' ') {
					((uint16 *)(0xb8000))[p.y * 80 + p.x] = c | attribute;
					p.x++;
				}

				// 每 80 个字符一行，满80就必须换行了
				if (p.x >= 80) {
					p.x = 0;
					p.y ++;
				}


				// cursor_y 到 25 的时候，就该换行了
				if (p.y >= 25) {
					uint16 blank = 0x20 | (((0 << 4) | (15 & 0x0F)) << 8);  // space 是 0x20
					// 将所有行的显示数据复制到上一行，第一行永远消失了...
					int i;
					for (i = 0 * 80; i < 24 * 80; i++) {
						videoMem[i] = videoMem[i+80];
					}

					// 最后的一行数据现在填充空格，不显示任何字符
					for (i = 24 * 80; i < 25 * 80; i++) {
						videoMem[i] = blank;
					}

					// 向上移动了一行，所以 cursor_y 现在是 24
					p.y = 24;
				}
			}
			void putc(char c, color back, color fore) {
				POINT p(x, y);
				putc_nomove(c, back, fore, p);
				
				// 移动硬件的输入光标
				move_cursor(p);
			}
			void puts(char str[], color back, color fore) {
				POINT p(x, y);
				for (int i = 0; str[i] != '\0'; i++) {
					putc_nomove(str[i], back, fore, p);
				}
				
				// 移动硬件的输入光标
				move_cursor(p);
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

				puts(buff);
			}
			void printk_color(color back, color fore, const char *format, ...)
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

			#define ZEROPAD		(1 << 0)	// pad with zero
			#define SIGN	 	(1 << 1)   	// unsigned/signed long
			#define PLUS    	(1 << 2)	// show plus
			#define SPACE	  	(1 << 3)   	// space if plus
			#define LEFT	 	(1 << 4)  	// left justified
			#define SPECIAL		(1 << 5)  	// 0x
			#define SMALL	  	(1 << 6)  	// use 'abcdef' instead of 'ABCDEF'

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
						len = strlen(s);
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
		namespace real_console = real;
	}
}