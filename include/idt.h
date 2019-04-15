#include "types.h"

namespace idt {
	// 初始化中断描述符表
	void init_idt();

	// 中断描述符
	typedef
	struct idt_entry_t {
		uint16 base_lo;        // 中断处理函数地址 15～0 位
		uint16 sel;            // 目标代码段描述符选择子
		uint8  always0;        // 置 0 段
		uint8  flags;          // 一些标志，文档有解释
		uint16 base_hi;        // 中断处理函数地址 31～16 位
	}__attribute__((packed)) idt_entry_t;

	// IDTR
	typedef
	struct idt_ptr_t {
		uint16 limit; 	// 限长
		uint32 base; 		// 基址
	} __attribute__((packed)) idt_ptr_t;

	// 寄存器类型
	typedef
	struct pt_regs_t {
		uint32 ds;		// 用于保存用户的数据段描述符
		uint32 edi; 		// 从 edi 到 eax 由 pusha 指令压入
		uint32 esi; 
		uint32 ebp;
		uint32 esp;
		uint32 ebx;
		uint32 edx;
		uint32 ecx;
		uint32 eax;
		uint32 int_no; 	// 中断号
		uint32 err_code;  	// 错误代码(有中断错误代码的中断会由CPU压入)
		uint32 eip;		// 以下由处理器自动压入
		uint32 cs; 		
		uint32 eflags;
		uint32 useresp;
		uint32 ss;
	} pt_regs;

	// 定义中断处理函数指针
	typedef void (*interrupt_handler_t)(pt_regs *);

	// 注册一个中断处理函数
	void register_interrupt_handler(uint8 n, interrupt_handler_t h);

	// 调用中断处理函数
	extern "C" void isr_handler(pt_regs *regs);
}

extern "C" {
	// 声明中断处理函数 0-19 属于 CPU 的异常中断
	// ISR:中断服务程序(interrupt service routine)
	void isr0(); 		// 0 #DE 除 0 异常 
	void isr1(); 		// 1 #DB 调试异常 
	void isr2(); 		// 2 NMI 
	void isr3(); 		// 3 BP 断点异常 
	void isr4(); 		// 4 #OF 溢出 
	void isr5(); 		// 5 #BR 对数组的引用超出边界 
	void isr6(); 		// 6 #UD 无效或未定义的操作码 
	void isr7(); 		// 7 #NM 设备不可用(无数学协处理器) 
	void isr8(); 		// 8 #DF 双重故障(有错误代码) 
	void isr9(); 		// 9 协处理器跨段操作 
	void isr10(); 		// 10 #TS 无效TSS(有错误代码) 
	void isr11(); 		// 11 #NP 段不存在(有错误代码) 
	void isr12(); 		// 12 #SS 栈错误(有错误代码) 
	void isr13(); 		// 13 #GP 常规保护(有错误代码) 
	void isr14(); 		// 14 #PF 页故障(有错误代码) 
	void isr15(); 		// 15 CPU 保留 
	void isr16(); 		// 16 #MF 浮点处理单元错误 
	void isr17(); 		// 17 #AC 对齐检查 
	void isr18(); 		// 18 #MC 机器检查 
	void isr19(); 		// 19 #XM SIMD(单指令多数据)浮点异常

	// 20-31 Intel 保留
	void isr20();
	void isr21();
	void isr22();
	void isr23();
	void isr24();
	void isr25();
	void isr26();
	void isr27();
	void isr28();
	void isr29();
	void isr30();
	void isr31();

	// 32～255 用户自定义异常
	/*
	void isr32();
	void isr33();
	void isr34();
	void isr35();
	void isr36();
	void isr37();
	void isr38();
	void isr39();

	void isr40(); void isr41(); void isr42(); void isr43(); void isr44();
	void isr45(); void isr46(); void isr47(); void isr48(); void isr49();
	void isr50(); void isr51(); void isr52(); void isr53(); void isr54();
	void isr55(); void isr56(); void isr57(); void isr58(); void isr59();
	void isr60(); void isr61(); void isr62(); void isr63(); void isr64();
	void isr65(); void isr66(); void isr67(); void isr68(); void isr69();
	void isr70(); void isr71(); void isr72(); void isr73(); void isr74();
	void isr75(); void isr76(); void isr77(); void isr78(); void isr79();
	void isr80(); void isr81(); void isr82(); void isr83(); void isr84();
	void isr85(); void isr86(); void isr87(); void isr88(); void isr89();
	void isr90(); void isr91(); void isr92(); void isr93(); void isr94();
	void isr95(); void isr96(); void isr97(); void isr98(); void isr99();
	void isr100(); void isr101(); void isr102(); void isr103(); void isr104();
	void isr105(); void isr106(); void isr107(); void isr108(); void isr109();
	void isr110(); void isr111(); void isr112(); void isr113(); void isr114();
	void isr115(); void isr116(); void isr117(); void isr118(); void isr119();
	void isr120(); void isr121(); void isr122(); void isr123(); void isr124();
	void isr125(); void isr126(); void isr127(); void isr128(); void isr129();
	void isr130(); void isr131(); void isr132(); void isr133(); void isr134();
	void isr135(); void isr136(); void isr137(); void isr138(); void isr139();
	void isr140(); void isr141(); void isr142(); void isr143(); void isr144();
	void isr145(); void isr146(); void isr147(); void isr148(); void isr149();
	void isr150(); void isr151(); void isr152(); void isr153(); void isr154();
	void isr155(); void isr156(); void isr157(); void isr158(); void isr159();
	void isr160(); void isr161(); void isr162(); void isr163(); void isr164();
	void isr165(); void isr166(); void isr167(); void isr168(); void isr169();
	void isr170(); void isr171(); void isr172(); void isr173(); void isr174();
	void isr175(); void isr176(); void isr177(); void isr178(); void isr179();
	void isr180(); void isr181(); void isr182(); void isr183(); void isr184();
	void isr185(); void isr186(); void isr187(); void isr188(); void isr189();
	void isr190(); void isr191(); void isr192(); void isr193(); void isr194();
	void isr195(); void isr196(); void isr197(); void isr198(); void isr199();

	void isr210(); void isr111(); void isr112(); void isr113(); void isr114();
	void isr115(); void isr116(); void isr117(); void isr118(); void isr119();
	void isr200(); void isr201(); void isr202(); void isr203(); void isr204();
	void isr205(); void isr206(); void isr207(); void isr208(); void isr209();
	void isr220(); void isr221(); void isr222(); void isr223(); void isr224();
	void isr225(); void isr226(); void isr227(); void isr228(); void isr229();
	void isr230(); void isr231(); void isr232(); void isr233(); void isr234();
	void isr235(); void isr236(); void isr237(); void isr238(); void isr239();
	void isr240(); void isr241(); void isr242(); void isr243(); void isr244();
	void isr245(); void isr246(); void isr247(); void isr248(); void isr249();
	void isr250(); void isr251(); void isr252(); void isr253(); void isr254();
	*/
	void isr255();
}
