#include "types.h"
#include "memManage.h"
using namespace memManage;

namespace memManage {
    const int gdtLength = 5;

    GDT_ENTRY gdtEntries[gdtLength];
    GDT_PTR gdt_ptr;

    // 全局描述符表构造函数，根据下标构造
    void gdt_set_gate(uint32 num, uint32 base, uint32 limit, uint8 access, uint8 gran);

    // 声明内核栈地址
    extern uint32 stack;
<<<<<<< HEAD
=======
    extern "C" void gdt_flush(GDT_PTR *pgdt);
    // extern "C" void gdt_flush(GDT_PTR *pgdt) {
    //     asm("mov    0x4(%esp),%eax\n\t");
    //     asm(".intel_syntax\n\t");
    //     asm("lgdt [%eax]\n\t");

    //     asm("jmp .flush\n\t");

    //     asm(".flush:\n\t");
    //     asm("mov %ax, 0x10\n\t");
    //     asm("mov %ds, %ax\n\t");
    //     asm("mov %es, %ax\n\t");
    //     asm("mov %fs, %ax\n\t");
    //     asm("mov %gs, %ax\n\t");
    //     asm("mov %ss, %ax\n\t");
    //     asm(".att_syntax\n\t");
    // }
>>>>>>> Reconstruct_using_module

    extern "C" void gdt_flush(GDT_PTR *pgdt);
    // 初始化全局描述符表
    void init_mm()
    {
        // 全局描述符表界限 e.g. 从 0 开始，所以总长要 - 1
        gdt_ptr.limit = sizeof(gdt_entry_t) * gdtLength - 1;
        gdt_ptr.base = (uint32)&gdtEntries;

        // 采用 Intel 平坦模型
        gdt_set_gate(0, 0, 0, 0, 0);             	// 按照 Intel 文档要求，第一个描述符必须全 0
        gdt_set_gate(1, 0, 0xFFFFFFFF, 0x9A, 0xCF); 	// 指令段
        gdt_set_gate(2, 0, 0xFFFFFFFF, 0x92, 0xCF); 	// 数据段
        gdt_set_gate(3, 0, 0xFFFFFFFF, 0xFA, 0xCF); 	// 用户模式代码段
        gdt_set_gate(4, 0, 0xFFFFFFFF, 0xF2, 0xCF); 	// 用户模式数据段

        gdt_flush(&gdt_ptr);
    }

    // 全局描述符表构造函数，根据下标构造
    // 参数分别是 数组下标、基地址、限长、访问标志，其它访问标志
    /* 结构体定义如下：
    typedef struct
    {
        uint16_t limit_low;     // 段界限   15～0
        uint16_t base_low;      // 段基地址 15～0
        uint8  base_middle;   // 段基地址 23～16
        uint8  access;        // 段存在位、描述符特权级、描述符类型、描述符子类别
        uint8  granularity; 	// 其他标志、段界限 19～16
        uint8  base_high;     // 段基地址 31～24
    } __attribute__((packed)) gdt_entry_t;
    */
    void gdt_set_gate(uint32 num, uint32 base, uint32 limit, uint8 access, uint8 gran)
    {
        gdtEntries[num].base_low     = (base & 0xFFFF);
        gdtEntries[num].base_middle  = (base >> 16) & 0xFF;
        gdtEntries[num].base_high    = (base >> 24) & 0xFF;

        gdtEntries[num].limit_low    = (limit & 0xFFFF);
        gdtEntries[num].granularity  = (limit >> 16) & 0x0F;

        gdtEntries[num].granularity |= gran & 0xF0;
        gdtEntries[num].access       = access;
    }
}

