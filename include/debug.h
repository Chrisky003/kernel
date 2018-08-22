#pragma once
#include "real_console.h"
#include "def.h"

namespace debug
{

	#define ELF32_ST_TYPE(i) ((i)&0xf)

	// ELF 格式区段头
	typedef
	struct elf_section_header_t {
  		uint32_t name;
  		uint32_t type;
  		uint32_t flags;
  		uint32_t addr;
  		uint32_t offset;
  		uint32_t size;
  		uint32_t link;
  		uint32_t info;
  		uint32_t addralign;
  		uint32_t entsize;
	} __attribute__((packed)) elf_section_header_t;

	// ELF 格式符号
	typedef
	struct elf_symbol_t {
		uint32_t name;
  		uint32_t value;
  		uint32_t size;
  		uint8_t  info;
  		uint8_t  other;
  		uint16_t shndx;
	} __attribute__((packed)) elf_symbol_t;

	// ELF 信息
	typedef
	struct elf_t {
  		elf_symbol_t *symtab;
  		uint32_t      symtabsz;
  		const char   *strtab;
  		uint32_t      strtabsz;
	} elf_t;

	// 从 multiboot_t 结构获取ELF信息
	elf_t elf_from_multiboot(multiboot_t *mb);

	// 查看ELF的符号信息
	const char *elf_lookup_symbol(uint32_t addr, elf_t *elf);


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
	void init_debug();

	// 打印当前的函数调用栈信息
	void panic(const char *msg);

	// 打印当前的段存器值
	void print_cur_status();

	// 内核的打印函数 带颜色
	void printk_color(real_color_t back, real_color_t fore, const char *format, ...);
}