#include "CKernel.h"
#include "CErrorReporter.h"
#include "io.h"
using namespace io;

CKernel::CKernel(multiboot_t *mb):
	memory(mb)
{
	this->mb = mb;
	CErrorReporter::init(mb);
}

CKernel::~CKernel()
{
	
}

void CKernel::run()
{
	
	console::real::print_color(console::real::color::green, \
		console::real::color::red, "Hello World!\n");
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
	CErrorReporter::panic("Test!");
}
