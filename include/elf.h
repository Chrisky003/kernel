#pragma once
#include "types.h"

namespace lib::elf {
    // 从 multiboot_t 结构获取ELF信息
    ELF elf_from_multiboot(MULTIBOOT *mb);

    // 查看ELF的符号信息
    const char *elf_lookup_symbol(uint32 addr, ELF *elf);
}