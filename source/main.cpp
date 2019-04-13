#include "types.h"
#include "io.h"
#include "debug.h"
#include "memManage.h"
#include "CModule.h"
#include "string.h"
#include "CModManager.h"
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

class CTest {
public:
	CTest() {
		puts("CTest Constructor.");
	}
	~CTest() {
		puts("CTest Destructor.");
	}
} test;

extern "C" int kernelEntry(MULTIBOOT *pmultiboot) {
	init_debug(pmultiboot);
	clear();
	puts("Hello World!\n", color::green, color::red);
	memManage::init_mm();
	puts("now run in protected mode.");

	//printk("0x%x\n", pmultiboot);
	//panic("Test!");
	modManager.init();
	return 0;
}