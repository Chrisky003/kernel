#include "types.h"
#include "io.h"
#include "debug.h"
using namespace io::console::real_console;
using namespace debug;

extern "C" int kernelEntry(MULTIBOOT *pmultiboot);

extern "C" int kernelEntry(MULTIBOOT *pmultiboot) {
	clear();
	puts("Hello World!\n", color::green, color::red);
	panic("Test!");
	return 0;
}