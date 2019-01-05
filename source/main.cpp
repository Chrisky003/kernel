#include "types.h"

extern "C" int kernelEntry(multiboot *pmultiboot);

extern "C" int kernelEntry(multiboot *pmultiboot) {
	uint8 *input = (uint8 *)0xB8000;
	uint8 color = (0 << 4) | (15 & 0x0f);
	char str[] = "Hello Kernel!\0";
	for (int i = 0; str[i] != '\0'; i++) {
		*input++ = str[i];
		*input++ = color;
	}
	return 0;
}