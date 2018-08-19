#pragma once
#include "def.h"

namespace memory
{
	byte read8(dword _where);
	void write8(dword _where, byte data);
	word read16(dword _where);
	void write16(dword _where, word data);
	dword read32(dword _where);
	void write32(dword _where, dword data);
	dword memcpy(void *dest, const void *src, int size);
	void memset(void *src, byte data, int size);
	void zeromem(void *src, int size);
	int *intToPointer(int i);
}
