#pragma once
#include "def.h"

class CMemory
{
public:
	CMemory(multiboot_t *mb);
	~CMemory();
public:
	void init_gdt();
private:
	static void get_set_gate(int num, dword base, int limit, byte access, byte gran);
public:
	// 全局描述符表长度
	#define GDT_LENGTH 5

	// 全局描述符表定义
	gdt_entry_t gdt_entries[GDT_LENGTH];

	// GDTR
	gdt_ptr_t gdt_ptr;
	multiboot_t *mb;
};

