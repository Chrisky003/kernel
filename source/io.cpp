#include "io.h"

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
			void putc(char c, color back, color fore) {
				uint16 attribute = ((back << 4) | (fore & 0x0F)) << 8;

				POINT p(x, y);
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

				// 移动硬件的输入光标
				move_cursor(p);
			}
			void puts(char str[], color back, color fore) {
				for (int i = 0; str[i] != '\0'; i++) {
					putc(str[i], back, fore);
				}
			}
		}
		namespace real_console = real;
	}
}