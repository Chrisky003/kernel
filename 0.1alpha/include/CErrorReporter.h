#pragma once
#include "def.h"

class CErrorReporter
{
public:
	static int ELF32_ST_TYPE(int i);
	// 从 multiboot_t 结构获取ELF信息
	static elf_t elf_from_multiboot(multiboot_t *mb);
	// 查看ELF的符号信息
	static const char *elf_lookup_symbol(dword addr, elf_t *elf);
	static void assert(int x, char* info);   
	// 编译期间静态检测
	#define static_assert(x) \
		switch (x) { case 0: case (x): ; }
	// 初始化 Debug 信息
	static void init(multiboot_t *mb);
	// 打印当前的函数调用栈信息
	static void panic(const char *msg);
	// 打印当前的段存器值
	static void print_cur_status();
	static void print_stack_trace();
	elf_t static kernel_elf;
};
