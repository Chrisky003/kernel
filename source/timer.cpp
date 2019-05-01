#include "idt.h"
#include "types.h"
#include "io.h"
using namespace io::port;
using namespace io::console::real;

int tick(0);

void timer_callback(idt::pt_regs *regs) {
    io::console::real::move_cursor(6, -1);
    printk("%d", tick++);
}

void init_timer(uint32 freq) {
    idt::register_interrupt_handler(IRQ0, timer_callback);
    uint32 divisor = 1193180 / freq;
    out8(0x43, 0x36);
    // 拆分低字节和高字节
    uint8 low = (uint8)(divisor & 0xFF);
    uint8 hign = (uint8)((divisor >> 8) & 0xFF);
    // 分别写入低字节和高字节
    out8(0x40, low);
    out8(0x40, hign);
    printk("Tick: ");
}