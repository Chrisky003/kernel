#include "def.h"
#include "CKernel.h"

void* _Unwind_Resume = nullptr;
void* __gxx_personality_v0 = nullptr;

extern "C" int entry(multiboot_t *mb);

extern "C" int entry(multiboot_t *mb)
{
	CKernel kernel(mb);
	kernel.run();
	return 0xab1ab1ab;
}
