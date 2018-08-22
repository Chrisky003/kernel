#include "debug.h"
#include "real_console.h"
#include "string.h"

namespace debug
{
	static void print_stack_trace();

	static elf_t kernel_elf;
	// 从 multiboot_t 结构获取ELF信息
	elf_t elf_from_multiboot(multiboot_t *mb)
	{
		int i;
		elf_t elf;
		elf_section_header_t *sh = (elf_section_header_t *)mb->addr;

		dword shstrtab = sh[mb->shndx].addr;
		for (i = 0; i < mb->num; i++) {
			const char *name = (const char *)(shstrtab + sh[i].name);
			// 在 GRUB 提供的 multiboot 信息中寻找内核 ELF 格式所提取的字符串表和符号表
			if (string::strcmp(name, ".strtab") == 0) {
				elf.strtab = (const char *)sh[i].addr;
				elf.strtabsz = sh[i].size;
			}
			if (string::strcmp(name, ".symtab") == 0) {
				elf.symtab = (elf_symbol_t *)sh[i].addr;
				elf.symtabsz = sh[i].size;
			}
		}

		return elf;
	}

	// 查看ELF的符号信息
	const char *elf_lookup_symbol(dword addr, elf_t *elf)
	{
		int i;

		for (i = 0; i < (elf->symtabsz / sizeof(elf_symbol_t)); i++) {
			if (ELF32_ST_TYPE(elf->symtab[i].info) != 0x2) {
				continue;
			}
			// 通过函数调用地址查到函数的名字(地址在该函数的代码段地址区间之内)
			if ( (addr >= elf->symtab[i].value) && (addr < (elf->symtab[i].value + elf->symtab[i].size)) ) {
				return (const char *)((dword)elf->strtab + elf->symtab[i].name);
			}
		}

		return NULL;
	}

	void init_debug(multiboot_t *mb)
	{
		// 从 GRUB 提供的信息中获取到内核符号表和代码地址信息
		kernel_elf = elf_from_multiboot(mb);
	}

	void print_cur_status()
	{
		static int round = 0;
		word reg1, reg2, reg3, reg4;

		asm volatile ( 	"mov %%cs, %0;"
			"mov %%ds, %1;"
			"mov %%es, %2;"
			"mov %%ss, %3;"
			: "=m"(reg1), "=m"(reg2), "=m"(reg3), "=m"(reg4));

		// 打印当前的运行级别
		real_console::print("%d: @ring %d\n", round, reg1 & 0x3);
		real_console::print("%d:  cs = %x\n", round, reg1);
		real_console::print("%d:  ds = %x\n", round, reg2);
		real_console::print("%d:  es = %x\n", round, reg3);
		real_console::print("%d:  ss = %x\n", round, reg4);
		++round;
	}

	void panic(const char *msg)
	{
		real_console::print("*** System panic: %s\n", msg);
		print_stack_trace();
		real_console::print("***\n");
	
	// 致命错误发生后打印栈信息后停止在这里
	while(1);
	}

	void print_stack_trace()
	{
		dword *ebp, *eip;

		asm volatile ("mov %%ebp, %0" : "=r" (ebp));
		while (ebp)
		{
			eip = ebp + 1;
			real_console::print("   [0x%x] %s\n", *eip, elf_lookup_symbol(*eip, &kernel_elf));
			ebp = (dword*)*ebp;
		}
	}
}