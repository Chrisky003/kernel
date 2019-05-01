#include "idt.h"
#include "io.h"
#include "string.h"
using namespace lib::string;
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
    void init_idt()
    {	
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
        IDT_SET_GATE(47); IDT_SET_GATE(48); IDT_SET_GATE(49); IDT_SET_GATE(50); IDT_SET_GATE(51); 
        IDT_SET_GATE(52); IDT_SET_GATE(53); IDT_SET_GATE(54); IDT_SET_GATE(55); IDT_SET_GATE(56); 
        IDT_SET_GATE(57); IDT_SET_GATE(58); IDT_SET_GATE(59); IDT_SET_GATE(60); IDT_SET_GATE(61); 
        IDT_SET_GATE(62); IDT_SET_GATE(63); IDT_SET_GATE(64); IDT_SET_GATE(65); IDT_SET_GATE(66); 
        IDT_SET_GATE(67); IDT_SET_GATE(68); IDT_SET_GATE(69); IDT_SET_GATE(70); IDT_SET_GATE(71); 
        IDT_SET_GATE(72); IDT_SET_GATE(73); IDT_SET_GATE(74); IDT_SET_GATE(75); IDT_SET_GATE(76); 
        IDT_SET_GATE(77); IDT_SET_GATE(78); IDT_SET_GATE(79); IDT_SET_GATE(80); IDT_SET_GATE(81); 
        IDT_SET_GATE(82); IDT_SET_GATE(83); IDT_SET_GATE(84); IDT_SET_GATE(85); IDT_SET_GATE(86); 
        IDT_SET_GATE(87); IDT_SET_GATE(88); IDT_SET_GATE(89); IDT_SET_GATE(90); IDT_SET_GATE(91); 
        IDT_SET_GATE(92); IDT_SET_GATE(93); IDT_SET_GATE(94); IDT_SET_GATE(95); IDT_SET_GATE(96); 
        IDT_SET_GATE(97); IDT_SET_GATE(98); IDT_SET_GATE(99); IDT_SET_GATE(100); IDT_SET_GATE(101); 
        IDT_SET_GATE(102); IDT_SET_GATE(103); IDT_SET_GATE(104); IDT_SET_GATE(105); IDT_SET_GATE(106); 
        IDT_SET_GATE(107); IDT_SET_GATE(108); IDT_SET_GATE(109); IDT_SET_GATE(110); IDT_SET_GATE(111); 
        IDT_SET_GATE(112); IDT_SET_GATE(113); IDT_SET_GATE(114); IDT_SET_GATE(115); IDT_SET_GATE(116); 
        IDT_SET_GATE(117); IDT_SET_GATE(118); IDT_SET_GATE(119); IDT_SET_GATE(120); IDT_SET_GATE(121); 
        IDT_SET_GATE(122); IDT_SET_GATE(123); IDT_SET_GATE(124); IDT_SET_GATE(125); IDT_SET_GATE(126); 
        IDT_SET_GATE(127); IDT_SET_GATE(128); IDT_SET_GATE(129); IDT_SET_GATE(130); IDT_SET_GATE(131); 
        IDT_SET_GATE(132); IDT_SET_GATE(133); IDT_SET_GATE(134); IDT_SET_GATE(135); IDT_SET_GATE(136); 
        IDT_SET_GATE(137); IDT_SET_GATE(138); IDT_SET_GATE(139); IDT_SET_GATE(140); IDT_SET_GATE(141); 
        IDT_SET_GATE(142); IDT_SET_GATE(143); IDT_SET_GATE(144); IDT_SET_GATE(145); IDT_SET_GATE(146); 
        IDT_SET_GATE(147); IDT_SET_GATE(148); IDT_SET_GATE(149); IDT_SET_GATE(150); IDT_SET_GATE(151); 
        IDT_SET_GATE(152); IDT_SET_GATE(153); IDT_SET_GATE(154); IDT_SET_GATE(155); IDT_SET_GATE(156); 
        IDT_SET_GATE(157); IDT_SET_GATE(158); IDT_SET_GATE(159); IDT_SET_GATE(160); IDT_SET_GATE(161); 
        IDT_SET_GATE(162); IDT_SET_GATE(163); IDT_SET_GATE(164); IDT_SET_GATE(165); IDT_SET_GATE(166); 
        IDT_SET_GATE(167); IDT_SET_GATE(168); IDT_SET_GATE(169); IDT_SET_GATE(170); IDT_SET_GATE(171); 
        IDT_SET_GATE(172); IDT_SET_GATE(173); IDT_SET_GATE(174); IDT_SET_GATE(175); IDT_SET_GATE(176); 
        IDT_SET_GATE(177); IDT_SET_GATE(178); IDT_SET_GATE(179); IDT_SET_GATE(180); IDT_SET_GATE(181); 
        IDT_SET_GATE(182); IDT_SET_GATE(183); IDT_SET_GATE(184); IDT_SET_GATE(185); IDT_SET_GATE(186); 
        IDT_SET_GATE(187); IDT_SET_GATE(188); IDT_SET_GATE(189); IDT_SET_GATE(190); IDT_SET_GATE(191); 
        IDT_SET_GATE(192); IDT_SET_GATE(193); IDT_SET_GATE(194); IDT_SET_GATE(195); IDT_SET_GATE(196); 
        IDT_SET_GATE(197); IDT_SET_GATE(198); IDT_SET_GATE(199); IDT_SET_GATE(200); IDT_SET_GATE(201); 
        IDT_SET_GATE(202); IDT_SET_GATE(203); IDT_SET_GATE(204); IDT_SET_GATE(205); IDT_SET_GATE(206); 
        IDT_SET_GATE(207); IDT_SET_GATE(208); IDT_SET_GATE(209); IDT_SET_GATE(210); IDT_SET_GATE(211); 
        IDT_SET_GATE(212); IDT_SET_GATE(213); IDT_SET_GATE(214); IDT_SET_GATE(215); IDT_SET_GATE(216); 
        IDT_SET_GATE(217); IDT_SET_GATE(218); IDT_SET_GATE(219); IDT_SET_GATE(220); IDT_SET_GATE(221); 
        IDT_SET_GATE(222); IDT_SET_GATE(223); IDT_SET_GATE(224); IDT_SET_GATE(225); IDT_SET_GATE(226); 
        IDT_SET_GATE(227); IDT_SET_GATE(228); IDT_SET_GATE(229); IDT_SET_GATE(230); IDT_SET_GATE(231); 
        IDT_SET_GATE(232); IDT_SET_GATE(233); IDT_SET_GATE(234); IDT_SET_GATE(235); IDT_SET_GATE(236); 
        IDT_SET_GATE(237); IDT_SET_GATE(238); IDT_SET_GATE(239); IDT_SET_GATE(240); IDT_SET_GATE(241); 
        IDT_SET_GATE(242); IDT_SET_GATE(243); IDT_SET_GATE(244); IDT_SET_GATE(245); IDT_SET_GATE(246); 
        IDT_SET_GATE(247); IDT_SET_GATE(248); IDT_SET_GATE(249); IDT_SET_GATE(250); IDT_SET_GATE(251); 
        IDT_SET_GATE(252); IDT_SET_GATE(253); IDT_SET_GATE(254);       
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
            irq_handler(regs);
        }
        else if (interrupt_handlers[regs->int_no]) {
            interrupt_handlers[regs->int_no](regs);
        }
        else {
            io::console::real::printk_color(io::console::real::color::black, io::console::real::color::blue, "Unhandled interrupt: %d\n", regs->int_no);
            //stop();
        }
    }

    void irq_handler(pt_regs *regs) {
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

        if (interrupt_handlers[regs->int_no]) {
            interrupt_handlers[regs->int_no](regs);
        }
    }

    // 注册一个中断处理函数
    void register_interrupt_handler(uint8 n, interrupt_handler_t h)
    {
        interrupt_handlers[n] = h;
    }
}
