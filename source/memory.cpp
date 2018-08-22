#include "memory.h"

namespace memory
{
	byte read8(dword _where)
	{
		union{dword* p; dword where;}data;
		data.where = _where;
		return *((byte*)data.p);
	}
	
	void write8(dword _where, byte data)
	{
		union{dword* p; dword where;}_data;
		_data.where = _where;
		*((byte*)_data.p) = data;
	}
	
	word read16(dword _where)
	{
		union{dword* p; dword where;}data;
		data.where = _where;
		return *(short*)data.p;
	}
	
	void write16(dword _where, word data)
	{
		union{dword* p; dword where;}_data;
		_data.where = _where;
		*((short*)_data.p) = data;
	}
	
	dword read32(dword _where)
	{
		union{dword* p; dword where;}data;
		data.where = _where;
		return *(dword*)data.p;
	}
	
	void write32(dword _where, dword data)
	{
		union{dword* p; dword where;}_data;
		_data.where = _where;
		*((dword*)_data.p) = data;
	}
	
	dword memcpy(void *dest, const void *src, int size)
	{
		byte *_dest((byte*)dest), *_src((byte*)src);
		int i;
		for (i = 0; i < size; i++)
		{
			_dest[i] = _src[i];
		}
		return ++i;
	}
	
	void memset(void *src, byte data, int size)
	{
		for (int i = 0; i < size; i++)
		{
			((byte*)src)[i] = data;
		}
	}
	
	void zeromem(void *src, int size)
	{
		memset(src, 0, size);
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
		return data;
	}

}
