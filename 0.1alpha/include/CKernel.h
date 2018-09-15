#include "def.h"
#include "CMemory.h"

int entry(multiboot_t *mb);

class CKernel
{
	friend int entry(multiboot_t *mb);
public:
	CKernel(multiboot_t *mb);
	~CKernel();
public:
	void run();
public:
	CMemory memory;
	multiboot_t *mb;
};