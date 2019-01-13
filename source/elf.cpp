#include "types.h"
#include "elf.h"
#include "string.h"

namespace lib::elf {
    // 从 multiboot_t 结构获取ELF信息
    ELF elf_from_multiboot(MULTIBOOT *mb)
    {
        int i;
        ELF elf;
        ELF_SECTION_HEADER *sh = (ELF_SECTION_HEADER*)mb->addr;

        uint32 shstrtab = sh[mb->shndx].addr;
        for (i = 0; i < mb->num; i++) {
            const char *name = (const char *)(shstrtab + sh[i].name);
            // 在 GRUB 提供的 multiboot 信息中寻找内核 ELF 格式所提取的字符串表和符号表
            if (lib::string::strcmp(name, ".strtab") == 0) {
                elf.strtab = (const char *)sh[i].addr;
                elf.strtabsz = sh[i].size;
            }
            if (lib::string::strcmp(name, ".symtab") == 0) {
                elf.symtab = (ELF_SYMBOL*)sh[i].addr;
                elf.symtabsz = sh[i].size;
            }
        }

        return elf;
    }

    // 查看ELF的符号信息
    const char *elf_lookup_symbol(uint32 addr, ELF *elf)
    {
        int i;

        for (i = 0; i < (elf->symtabsz / sizeof(ELF_SYMBOL)); i++) {
            if (ELF32_ST_TYPE(elf->symtab[i].info) != 0x2) {
                continue;
            }
            // 通过函数调用地址查到函数的名字(地址在该函数的代码段地址区间之内)
            if ( (addr >= elf->symtab[i].value) && (addr < (elf->symtab[i].value + elf->symtab[i].size)) ) {
                return (const char *)((uint32)elf->strtab + elf->symtab[i].name);
            }
        }

        return NULL;
    }
}