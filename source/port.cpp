#include "port.h"

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
