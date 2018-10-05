#include "io.h"

namespace io
{

	namespace memory
	{
		byte in8(dword _where)
		{
			union{dword* p; dword where;}data;
			data.where = _where;
			return *((byte*)data.p);
		}
		
		void out8(dword _where, byte data)
		{
			union{dword* p; dword where;}_data;
			_data.where = _where;
			*((byte*)_data.p) = data;
		}
		
		word in16(dword _where)
		{
			union{dword* p; dword where;}data;
			data.where = _where;
			return *(short*)data.p;
		}
		
		void out16(dword _where, word data)
		{
			union{dword* p; dword where;}_data;
			_data.where = _where;
			*((short*)_data.p) = data;
		}
		
		dword in32(dword _where)
		{
			union{dword* p; dword where;}data;
			data.where = _where;
			return *(dword*)data.p;
		}
		
		void out32(dword _where, dword data)
		{
			union{dword* p; dword where;}_data;
			_data.where = _where;
			*((dword*)_data.p) = data;
		}
		
		dword copy(void *dest, const void *src, int size)
		{
			byte *_dest((byte*)dest), *_src((byte*)src);
			int i;
			for (i = 0; i < size; i++)
			{
				_dest[i] = _src[i];
			}
			return ++i;
		}
		
		void set(void *src, byte data, int size)
		{
			for (int i = 0; i < size; i++)
			{
				((byte*)src)[i] = data;
			}
		}
		
		void zero(void *src, int size)
		{
			set(src, 0, size);
		}
		
		int *intToPointer(int i)
		{
			union{int* p; int data;} uni;
			uni.data = i;
			return uni.p;
		}

		int pointerToInt(void *p)
		{
			union{int* p; int data;} uni;
			uni.p = (int*)p;
			return uni.data;
		}
	}

	namespace port
	{
		void out8(word port, byte value)
		{
			asm volatile ("outb %1, %0" : : "dN" (port), "a" (value));
		}
		
		byte in8(word port)
		{
			byte ret;
			asm volatile("inb %1, %0" : "=a" (ret) : "dN" (port));
			return ret;
		}
		
		word in16(word port)
		{
			word ret;
			asm volatile ("inw %1, %0" : "=a" (ret) : "dN" (port));
			return ret;
		}
	}

	namespace console
	{
		namespace real
		{
			const int width = 80;
			const int height = 25;

			POINT cursorPos;

			POINT getCursorPos()
			{
				return cursorPos;
			}

			void setCursorPos(POINT p)
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
					memory::out16(0xb8000, ' ' | \
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
					memory::out16(0xb8000 + (curpos.y * 80 + curpos.x) * 2, c | \
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
					memory::copy(uni.p, uni2.p, width * (height - 1) * 2);
					uni2.data = 0xb8000 + (height - 1) * width * 2;
					memory::set(uni2.p, (char)'\0', width * 1 * 2);
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

			void print(const char *format, ...)
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

			void print_color(color back, \
				color fore, const char *format, ...)
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

			inline bool is_digit(char c)
			{
				return c >= '0' && c <= '9';
			}	

			inline int skip_atoi(const char **s)
			{
				int i = 0;

				while (is_digit(**s))
				{
					i = i * 10 + *((*s)++) - '0';
				}

				return i;
			}

			const int ZEROPAD	= 1 >> 0;	// pad with zero
			const int SIGN		= 1 >> 1;	// unsigned/signed long
			const int PLUS		= 1 >> 2;	// show plus
			const int SPACE		= 1 >> 3;	// space if plus
			const int LEFT		= 1 >> 4;	// left justified
			const int SPECIAL	= 1 >> 5;	// 0x
			const int SMALL		= 1 >> 6;	// use 'abcdef' instead of 'ABCDEF'

			inline int do_div(int n, int base) 
			{
				int __res;
				__asm__("divl %4":"=a" (n),"=d" (__res):"0" (n),"1" (0),"r" (base));
				return __res; 
			}

			static char *number(char *str, int num, int base, int size, int precision, int type)
			{
				char c, sign, tmp[36];
				const char *digits = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
				int i;

				if (type & SMALL)
				{
					digits ="0123456789abcdefghijklmnopqrstuvwxyz";
				}
				if (type & LEFT) 
				{
					type &= ~ZEROPAD;
				}
				if (base < 2 || base > 36)
				{
					return 0;
				}

				c = (type & ZEROPAD) ? '0' : ' ' ;

				if (type & SIGN && num < 0) 
				{
					sign = '-';
					num = -num;
				} 
				else 
				{
					sign = (type&PLUS) ? '+' : ((type&SPACE) ? ' ' : 0);
				}

				if (sign) 
				{
					size--;
				}
				if (type & SPECIAL) 
				{
					if (base == 16) 
					{
						size -= 2;
					} 
					else if (base == 8) 
					{
						size--;
					}
				}
				i = 0;
				if (num == 0) 
				{
					tmp[i++] = '0';
				} 
				else 
				{
					while (num != 0) 
					{
						tmp[i++] = digits[do_div(num,base)];
					}
				}

				if (i > precision) 
				{
					precision = i;
				}
				size -= precision;

				if (!(type&(ZEROPAD+LEFT))) 
				{
					while (size-- > 0) 
					{
						*str++ = ' ';
					}
				}
				if (sign) 
				{
					*str++ = sign;
				}
				if (type & SPECIAL) 
				{
					if (base == 8) 
					{
						*str++ = '0';
					} 
					else if (base == 16) 
					{
						*str++ = '0';
						*str++ = digits[33];
					}
				}
				if (!(type&LEFT)) 
				{
					while (size-- > 0) 
					{
						*str++ = c;
					}
				}
				while (i < precision--) 
				{
					*str++ = '0';
				}
				while (i-- > 0) 
				{
					*str++ = tmp[i];
				}
				while (size-- > 0) 
				{
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

				for (str = buff ; *format ; ++format)
				{
					if (*format != '%') 
					{
						*str++ = *format;
						continue;
					}
						
					flags = 0;
					repeat:
						++format;		// this also skips first '%'
						switch (*format) 
						{
							case '-': 
							{
								flags |= LEFT;
								goto repeat;
							}
							case '+': 
							{
								flags |= PLUS;
								goto repeat;
							}
							case ' ': 
							{
								flags |= SPACE;
								goto repeat;
							}
							case '#': 
							{
								flags |= SPECIAL;
								goto repeat;
							}
							case '0': 
							{
								flags |= ZEROPAD;
								goto repeat;
							}
						}
					
					// get field width
					field_width = -1;
					if (is_digit(*format)) 
					{
						field_width = skip_atoi(&format);
					} 
					else if (*format == '*') 
					{
						// it's the next argument
						field_width = va_arg(args, int);
						if (field_width < 0) 
						{
							field_width = -field_width;
							flags |= LEFT;
						}
					}

					// get the precision
					precision = -1;
					if (*format == '.') 
					{
						++format;	
						if (is_digit(*format)) 
						{
							precision = skip_atoi(&format);
						} 
						else if (*format == '*') 
						{
							// it's the next argument
							precision = va_arg(args, int);
						}
						if (precision < 0) 
						{
							precision = 0;
						}
					}

					// get the conversion qualifier
					//int qualifier = -1;	// 'h', 'l', or 'L' for integer fields
					if (*format == 'h' || *format == 'l' || *format == 'L') 
					{
						//qualifier = *format;
						++format;
					}

					switch (*format) 
					{
						case 'c':
						{
							if (!(flags & LEFT)) 
							{
								while (--field_width > 0) 
								{
									*str++ = ' ';
								}
							}
							*str++ = (unsigned char) va_arg(args, int);
							while (--field_width > 0) 
							{
								*str++ = ' ';
							}
							break;
						}
						case 's':
						{
							s = va_arg(args, char *);
							len = string::strlen(s);
							if (precision < 0) 
							{
								precision = len;
							} 
							else if (len > precision) 
							{
								len = precision;
							}

							if (!(flags & LEFT)) 
							{
								while (len < field_width--) 
								{
									*str++ = ' ';
								}
							}
							for (i = 0; i < len; ++i) 
							{
								*str++ = *s++;
							}
							while (len < field_width--) 
							{
								*str++ = ' ';
							}
							break;
						}
						case 'o':
						{
							str = number(str, va_arg(args, unsigned long), 8,
								field_width, precision, flags);
							break;
						}
						case 'p':
						{
							if (field_width == -1) 
							{
								field_width = 8;
								flags |= ZEROPAD;
							}
							str = number(str, (unsigned long) va_arg(args, void *), 16,
								field_width, precision, flags);
							break;
						}
						case 'x':
						{
							flags |= SMALL;
						}
						case 'X':
						{
							str = number(str, va_arg(args, unsigned long), 16,
								field_width, precision, flags);
							break;
						}
						case 'd':
						case 'i':
						{
							flags |= SIGN;
						}
						case 'u':
						{
							str = number(str, va_arg(args, unsigned long), 10,
								field_width, precision, flags);
							break;
						}
						case 'b':
						{
							str = number(str, va_arg(args, unsigned long), 2,
								field_width, precision, flags);
							break;
						}
						case 'n':
						{
							ip = va_arg(args, int *);
							*ip = (str - buff);
							break;
						}
						default:
						{
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
				}
				*str = '\0';
				return (str -buff);
			}
		}

		// namespace virtual
		// {
		// }
	}

	namespace string
	{
		int strlen(const char *str)
		{
			int len = 0;
			while (str[len] != 0)
			{
				len++;
			}
			return ++len;
		}
		
		int strcpy(char *dest, const char *src)
		{
			int len = strlen(dest);
			memory::copy(dest, src, len);
			return ++len;
		}
		
		int strcmp(const char *str1, const char *str2)
		{
			for(;*str1==*str2;++str1,++str2)
				if(*str1=='\0')
					return(0);
			return((*(unsigned char*)str1<*(unsigned char*)str2)?-1:+1);
		}
	}
}