#include "types.h"
#include "io.h"
#include "debug.h"
#include "memManage.h"
#include "CModule.h"
#include "string.h"
using namespace io::console::real_console;
using namespace debug;

extern "C" int kernelEntry(MULTIBOOT *pmultiboot);

extern "C" int kernelEntry(MULTIBOOT *pmultiboot) {
	init_debug(pmultiboot);
	memManage::init_mm();
	clear();
	puts("Hello World!\n", color::green, color::red);
	printk("%h\n", pmultiboot);
	panic("Test!");
	return 0;
}