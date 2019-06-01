#include "mm/idt.h"
#include "stdlib.h"
using namespace io::port;
extern "C" void stop();

namespace idt {
    // 中断描述符表
    idt_entry_t idt_entries[256];

    // IDTR
    idt_ptr_t idt_ptr;

    // 中断处理函数的指针数组
    interrupt_handler_t interrupt_handlers[256];

    // 设置中断描述符
    static void idt_set_gate(uint8 num, uint32 base, uint16 sel = 0x08, uint8 flags = 0x8E);

    // 声明加载 IDTR 的函数
    extern "C" void idt_flush(uint32);

    // 初始化中断描述符表
    void init_idt() {	
        bzero((uint8 *)&interrupt_handlers, sizeof(interrupt_handler_t) * 256);
        
        idt_ptr.limit = sizeof(idt_entry_t) * 256 - 1;
        idt_ptr.base  = (uint32)&idt_entries;
        
        bzero((uint8 *)&idt_entries, sizeof(idt_entry_t) * 256);
        #define IDT_SET_GATE(n,arg...) idt_set_gate(n,(uint32)isr##n,##arg)
        // 0-32:  用于 CPU 的中断处理
        idt_set_gate( 0, (uint32)isr0,  0x08, 0x8E);
        idt_set_gate( 1, (uint32)isr1,  0x08, 0x8E);
        idt_set_gate( 2, (uint32)isr2,  0x08, 0x8E);
        idt_set_gate( 3, (uint32)isr3,  0x08, 0x8E);
        idt_set_gate( 4, (uint32)isr4,  0x08, 0x8E);
        idt_set_gate( 5, (uint32)isr5,  0x08, 0x8E);
        idt_set_gate( 6, (uint32)isr6,  0x08, 0x8E);
        idt_set_gate( 7, (uint32)isr7,  0x08, 0x8E);
        idt_set_gate( 8, (uint32)isr8,  0x08, 0x8E);
        idt_set_gate( 9, (uint32)isr9,  0x08, 0x8E);
        idt_set_gate(10, (uint32)isr10, 0x08, 0x8E);
        idt_set_gate(11, (uint32)isr11, 0x08, 0x8E);
        idt_set_gate(12, (uint32)isr12, 0x08, 0x8E);
        idt_set_gate(13, (uint32)isr13, 0x08, 0x8E);
        idt_set_gate(14, (uint32)isr14, 0x08, 0x8E);
        idt_set_gate(15, (uint32)isr15, 0x08, 0x8E);
        idt_set_gate(16, (uint32)isr16, 0x08, 0x8E);
        idt_set_gate(17, (uint32)isr17, 0x08, 0x8E);
        idt_set_gate(18, (uint32)isr18, 0x08, 0x8E);
        idt_set_gate(19, (uint32)isr19, 0x08, 0x8E);
        idt_set_gate(20, (uint32)isr20, 0x08, 0x8E);
        idt_set_gate(21, (uint32)isr21, 0x08, 0x8E);
        idt_set_gate(22, (uint32)isr22, 0x08, 0x8E);
        idt_set_gate(23, (uint32)isr23, 0x08, 0x8E);
        idt_set_gate(24, (uint32)isr24, 0x08, 0x8E);
        idt_set_gate(25, (uint32)isr25, 0x08, 0x8E);
        idt_set_gate(26, (uint32)isr26, 0x08, 0x8E);
        idt_set_gate(27, (uint32)isr27, 0x08, 0x8E);
        idt_set_gate(28, (uint32)isr28, 0x08, 0x8E);
        idt_set_gate(29, (uint32)isr29, 0x08, 0x8E);
        idt_set_gate(30, (uint32)isr30, 0x08, 0x8E);
        idt_set_gate(31, (uint32)isr31, 0x08, 0x8E);

        IDT_SET_GATE(32); IDT_SET_GATE(33); IDT_SET_GATE(34); IDT_SET_GATE(35); IDT_SET_GATE(36); 
        IDT_SET_GATE(37); IDT_SET_GATE(38); IDT_SET_GATE(39); IDT_SET_GATE(40); IDT_SET_GATE(41); 
        IDT_SET_GATE(42); IDT_SET_GATE(43); IDT_SET_GATE(44); IDT_SET_GATE(45); IDT_SET_GATE(46); 
        IDT_SET_GATE(47); 
        for (int i = 48; i < 255; i++) {
            idt_set_gate(i, (uint32)isr48, 0x08, 0x8E);
        }
        // 255 将来用于实现系统调用
        idt_set_gate(255, (uint32)isr255, 0x08, 0x8E);

        out8(0x20, 0x11);
        out8(0xA0, 0x11);
        out8(0x21, 0x20);
        out8(0xA1, 0x28);
        out8(0x21, 0x04);
        out8(0xA1, 0x02);
        out8(0x21, 0x01);
        out8(0xA1, 0x01);
        out8(0x21, 0x0);
        out8(0xA1, 0x0);

        // 更新设置中断描述符表
        idt_flush((uint32)&idt_ptr);
    }

    // 设置中断描述符
    static void idt_set_gate(uint8 num, uint32 base, uint16 sel, uint8 flags)
    {
        idt_entries[num].base_lo = base & 0xFFFF;
        idt_entries[num].base_hi = (base >> 16) & 0xFFFF;

        idt_entries[num].sel     = sel;
        idt_entries[num].always0 = 0;

        // 先留下 0x60 这个魔数，以后实现用户态时候
        // 这个与运算可以设置中断门的特权级别为 3
        idt_entries[num].flags = flags;  // | 0x60
    }

    // 调用中断处理函数
    extern "C" void isr_handler(pt_regs *regs)
    {
        if (regs->int_no >= 32 && regs->int_no <= 47) {
            // 发送中断结束信号给 PICs
            // 按照我们的设置，从 32 号中断起为用户自定义中断
            // 因为单片的 Intel 8259A 芯片只能处理 8 级中断
            // 故大于等于 40 的中断号是由从片处理的
            if (regs->int_no >= 40) {
                // 发送重设信号给从片
               out8(0xA0, 0x20);
            }
            // 发送重设信号给主片
            out8(0x20, 0x20);
        }
        if (interrupt_handlers[regs->int_no]) {
            interrupt_handlers[regs->int_no](regs);
        }
        else {
            io::console::real::printk_color(io::console::real::color::black, io::console::real::color::blue, "Unhandled interrupt: %d\n", regs->int_no);
            //stop();
        }
    }

    // 注册一个中断处理函数
    void register_interrupt_handler(uint8 n, interrupt_handler_t h)
    {
        interrupt_handlers[n] = h;
    }
}

