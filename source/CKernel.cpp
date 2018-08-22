#include "CKernel.h"
#include "real_console.h"
#include "debug.h"

CKernel::CKernel(multiboot_t *mb):
	memory(mb)
{
	this->mb = mb;
}

CKernel::~CKernel()
{
	
}

void CKernel::run()
{
	debug::init_debug(mb);
	real_console::print_color(real_console::color::green, real_console::color::red, "Hello World!\n");
	// int sum = 0;
	// int i = '0' - 1;
		
	// while (true)
	// {
		int delay = 100000;
		while(delay--);
		// real_console::putc(sum % 10 + i + 1, static_cast<real_console::color>(sum / 16), /*real_console::color::red*/static_cast<real_console::color>(sum % 16));
		// sum++;
		// sum %= 1280;
	// }
	debug::panic("Test!");
}
