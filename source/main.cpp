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
		puts("CTest Constructor.\n");
	}
	~CTest() {
		puts("CTest Destructor.\n");
	}
public:
	void func() {
		puts("now run in \"void CTest::func()\"\n");
		puts("now run out of \"void CTest::func()\"\n");
	}
} test;

CTest test2;

extern "C" int kernelEntry(MULTIBOOT *pmultiboot) {
	CTest test3;
	test.func();
	test2.func();
	test3.func();
	init_debug(pmultiboot);
	// clear();
	puts("Hello World!\n", color::green, color::red);
	memManage::init_mm();
	puts("now run in protected mode.\n");

	//printk("0x%x\n", pmultiboot);
	//panic("Test!");
	modManager.init();
	return 0;
}