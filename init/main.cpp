#include "stdlib.h"
#include "debug/debug.h"
#include "mm/memManage.h"
#include "mm/idt.h"
#include "timer/timer.h"
using namespace io::console::real_console;
using namespace debug;

extern "C" {
	//void *__dso_handle = 0;
	int kernelEntry(MULTIBOOT *pmultiboot);
}
extern "C" MULTIBOOT *glb_mboot_ptr;

int main() {
	return kernelEntry(glb_mboot_ptr);
}

extern "C" int kernelEntry(MULTIBOOT *pmultiboot) {
	init_debug(pmultiboot);
	// clear();
	puts("Hello World!\n", color::green, color::red);
	memManage::init_mm();
	puts("now run in protected mode.\n");

    idt::init_idt();
	printk("interrupt test\n");
	asm("int $255");
	asm("int $80");
	//printk("0x%x\n", pmultiboot);
	//panic("Test!");
	printk("interrupt test finished.\n");
	putc('\n');
	init_timer(1000);
	asm("sti");
	return 0;
}