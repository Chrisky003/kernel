#pragma once
#include "real_console.h"
#include "def.h"

namespace debug
{

	#define ELF32_ST_TYPE(i) ((i)&0xf)

	// ELF 格式区段头
	typedef
	struct elf_section_header_t {
  		dword name;
  		dword type;
  		dword flags;
  		dword addr;
  		dword offset;
  		dword size;
  		dword link;
  		dword info;
  		dword addralign;
  		dword entsize;
	} __attribute__((packed)) elf_section_header_t;

	// ELF 格式符号
	typedef
	struct elf_symbol_t {
		dword name;
  		dword value;
  		dword size;
  		byte  info;
  		byte  other;
  		word shndx;
	} __attribute__((packed)) elf_symbol_t;

	// ELF 信息
	typedef
	struct elf_t {
  		elf_symbol_t *symtab;
  		dword      symtabsz;
  		const char   *strtab;
  		dword      strtabsz;
	} elf_t;

	// 从 multiboot_t 结构获取ELF信息
	elf_t elf_from_multiboot(multiboot_t *mb);

	// 查看ELF的符号信息
	const char *elf_lookup_symbol(dword addr, elf_t *elf);


	#define assert(x, info)                                       	\
		do {                                                	\
			if (!(x)) {                                     \
				panic(info); 		     		\
			}                                               \
		} while (0)

	// 编译期间静态检测
	#define static_assert(x)                                	\
		switch (x) { case 0: case (x): ; }

	// 初始化 Debug 信息
	void init_debug(multiboot_t *mb);

	// 打印当前的函数调用栈信息
	void panic(const char *msg);

	// 打印当前的段存器值
	void print_cur_status();

	// 内核的打印函数 带颜色
	void printk_color(real_console::color back, real_console::color fore, const char *format, ...);
}