#include "types.h"
#include "io.h"
using namespace io::console::real_console;

extern "C" int kernelEntry(multiboot *pmultiboot);

extern "C" int kernelEntry(multiboot *pmultiboot) {
	clear();
	puts("Hello World!", color::green, color::red);
	return 0;
}