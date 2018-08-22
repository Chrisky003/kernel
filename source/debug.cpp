#include "debug.h"
#include "real_console.h"

namespace debug
{
	static void print_stack_trace();

	static elf_t kernel_elf;

	void init_debug()
	{
		// 从 GRUB 提供的信息中获取到内核符号表和代码地址信息
		kernel_elf = elf_from_multiboot(glb_mboot_ptr);
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
		reak_console::print("%d:  ds = %x\n", round, reg2);
		real_console::print("%d:  es = %x\n", round, reg3);
		real_console::print("%d:  ss = %x\n", round, reg4);
		++round;
	}

	void panic(const char *msg)
	{
		real_conosle::print("*** System panic: %s\n", msg);
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
			ebp = (uint32_t*)*ebp;
		}
	}
}