#include "types.h"
#include "mm/idt.h"
#include "mm/paging.h"
#include "io.h"
using namespace io::console::real;
namespace paging {
    PDE pd[1024]__attribute__((section(".page.needed")));
    PTE pt[1024][1024]__attribute__((section(".page.needed")));
    uint32 fpbitmap[1024 / 32];
    inline void setbit(unsigned int &data, unsigned int pos) {
        asm("bts %%eax,%0"::"m"(data),"a"(pos));
    }
    inline void clrbit(unsigned int &data, unsigned int pos) {
        asm("btc %%eax,%0"::"m"(data),"a"(pos));
    }
    inline int getbit(unsigned int &data, unsigned int pos) {
        asm("bt %%eax,%0"::"m"(data),"a"(pos));
        asm("jc L1");
        asm("mov $0, %eax");
        asm("pop %ebp");
        asm("ret");
        asm("L1:");
        return 1;
    }
    void init() {
        int size((kern_end - kern_start + 1023) / 1024);
        for (int i = 0; i < (size + 1023) / 1024; i++) {
            pd[i].flag_addr_and_zero = (int)&pt[i][0] | 0x3;
        }
        for (int i = 0; i < size; i += 4) {
            pt[0][i].flag_addr_and_zero= (i << 12) | 0x3;
        }
        asm("mov %0, %%cr3"::"r"(&pd));

        uint32 cr0;
        // 启用分页,将 cr0 寄存器的分页位置为 1 就好
        asm volatile ("mov %%cr0, %0" : "=r" (cr0));
        cr0 |= 0x80000000;
        asm volatile ("mov %0, %%cr0" : : "r" (cr0));
        idt::register_interrupt_handler(14, pageFaultHandler);
        return;
    }
    void pageFaultHandler(idt::pt_regs pregs) {
        printk("interrupt 14(page fault) handled!");
    }
}