#pragma once
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

	// IRQ 处理函数
	void irq_handler(pt_regs *regs);
}

extern "C" {
    #define ISR(n) void isr##n()
	// 声明中断处理函数 0-19 属于 CPU 的异常中断
	// ISR:中断服务程序(interrupt service routine)
	ISR(0); 		// 0 #DE 除 0 异常 
	ISR(1); 		// 1 #DB 调试异常 
	ISR(2); 		// 2 NMI 
	ISR(3); 		// 3 BP 断点异常 
	ISR(4); 		// 4 #OF 溢出 
	ISR(5); 		// 5 #BR 对数组的引用超出边界 
	ISR(6); 		// 6 #UD 无效或未定义的操作码 
	ISR(7); 		// 7 #NM 设备不可用(无数学协处理器) 
	ISR(8); 		// 8 #DF 双重故障(有错误代码) 
	ISR(9); 		// 9 协处理器跨段操作 
	ISR(10); 		// 10 #TS 无效TSS(有错误代码) 
	ISR(11); 		// 11 #NP 段不存在(有错误代码) 
	ISR(12); 		// 12 #SS 栈错误(有错误代码) 
	ISR(13); 		// 13 #GP 常规保护(有错误代码) 
	ISR(14); 		// 14 #PF 页故障(有错误代码) 
	ISR(15); 		// 15 CPU 保留 
	ISR(16); 		// 16 #MF 浮点处理单元错误 
	ISR(17); 		// 17 #AC 对齐检查 
	ISR(18); 		// 18 #MC 机器检查 
	ISR(19); 		// 19 #XM SIMD(单指令多数据)浮点异常

	// 20-31 Intel 保留
	ISR(20);
    ISR(21);
    ISR(22);
    ISR(23);
    ISR(24);
    ISR(25);
    ISR(26);
    ISR(27);
    ISR(28);
    ISR(29);
    ISR(30);
    ISR(31);

	// 32～255 用户自定义异常
    ISR(32); ISR(33); ISR(34); ISR(35); ISR(36); 
    ISR(37); ISR(38); ISR(39); ISR(40); ISR(41); 
    ISR(42); ISR(43); ISR(44); ISR(45); ISR(46); 
    ISR(47); ISR(48); ISR(49); ISR(50); ISR(51); 
    ISR(52); ISR(53); ISR(54); ISR(55); ISR(56); 
    ISR(57); ISR(58); ISR(59); ISR(60); ISR(61); 
    ISR(62); ISR(63); ISR(64); ISR(65); ISR(66); 
    ISR(67); ISR(68); ISR(69); ISR(70); ISR(71); 
    ISR(72); ISR(73); ISR(74); ISR(75); ISR(76); 
    ISR(77); ISR(78); ISR(79); ISR(80); ISR(81); 
    ISR(82); ISR(83); ISR(84); ISR(85); ISR(86); 
    ISR(87); ISR(88); ISR(89); ISR(90); ISR(91); 
    ISR(92); ISR(93); ISR(94); ISR(95); ISR(96); 
    ISR(97); ISR(98); ISR(99); ISR(100); ISR(101); 
    ISR(102); ISR(103); ISR(104); ISR(105); ISR(106); 
    ISR(107); ISR(108); ISR(109); ISR(110); ISR(111); 
    ISR(112); ISR(113); ISR(114); ISR(115); ISR(116); 
    ISR(117); ISR(118); ISR(119); ISR(120); ISR(121); 
    ISR(122); ISR(123); ISR(124); ISR(125); ISR(126); 
    ISR(127); ISR(128); ISR(129); ISR(130); ISR(131); 
    ISR(132); ISR(133); ISR(134); ISR(135); ISR(136); 
    ISR(137); ISR(138); ISR(139); ISR(140); ISR(141); 
    ISR(142); ISR(143); ISR(144); ISR(145); ISR(146); 
    ISR(147); ISR(148); ISR(149); ISR(150); ISR(151); 
    ISR(152); ISR(153); ISR(154); ISR(155); ISR(156); 
    ISR(157); ISR(158); ISR(159); ISR(160); ISR(161); 
    ISR(162); ISR(163); ISR(164); ISR(165); ISR(166); 
    ISR(167); ISR(168); ISR(169); ISR(170); ISR(171); 
    ISR(172); ISR(173); ISR(174); ISR(175); ISR(176); 
    ISR(177); ISR(178); ISR(179); ISR(180); ISR(181); 
    ISR(182); ISR(183); ISR(184); ISR(185); ISR(186); 
    ISR(187); ISR(188); ISR(189); ISR(190); ISR(191); 
    ISR(192); ISR(193); ISR(194); ISR(195); ISR(196); 
    ISR(197); ISR(198); ISR(199); ISR(200); ISR(201); 
    ISR(202); ISR(203); ISR(204); ISR(205); ISR(206); 
    ISR(207); ISR(208); ISR(209); ISR(210); ISR(211); 
    ISR(212); ISR(213); ISR(214); ISR(215); ISR(216); 
    ISR(217); ISR(218); ISR(219); ISR(220); ISR(221); 
    ISR(222); ISR(223); ISR(224); ISR(225); ISR(226); 
    ISR(227); ISR(228); ISR(229); ISR(230); ISR(231); 
    ISR(232); ISR(233); ISR(234); ISR(235); ISR(236); 
    ISR(237); ISR(238); ISR(239); ISR(240); ISR(241); 
    ISR(242); ISR(243); ISR(244); ISR(245); ISR(246); 
    ISR(247); ISR(248); ISR(249); ISR(250); ISR(251); 
    ISR(252); ISR(253); ISR(254); ISR(255);

	// 定义IRQ
	#define  IRQ0     32 	// 电脑系统计时器
	#define  IRQ1     (IRQ0 + 1) 	// 键盘
	#define  IRQ2     (IRQ0 + 2) 	// 与 IRQ9 相接，MPU-401 MD 使用
	#define  IRQ3     (IRQ0 + 3) 	// 串口设备
	#define  IRQ4     (IRQ0 + 4) 	// 串口设备
	#define  IRQ5     (IRQ0 + 5) 	// 建议声卡使用
	#define  IRQ6     (IRQ0 + 6) 	// 软驱传输控制使用
	#define  IRQ7     (IRQ0 + 7) 	// 打印机传输控制使用
	#define  IRQ8     (IRQ0 + 8) 	// 即时时钟
	#define  IRQ9     (IRQ0 + 9) 	// 与 IRQ2 相接，可设定给其他硬件
	#define  IRQ10    (IRQ0 + 10) 	// 建议网卡使用
	#define  IRQ11    (IRQ0 + 11) 	// 建议 AGP 显卡使用
	#define  IRQ12    (IRQ0 + 12)	// 接 PS/2 鼠标，也可设定给其他硬件
	#define  IRQ13    (IRQ0 + 13) 	// 协处理器使用
	#define  IRQ14    (IRQ0 + 14) 	// IDE0 传输控制使用
	#define  IRQ15    (IRQ0 + 15) 	// IDE1 传输控制使用

	#define IRQ(n) void irq##n()

	// 声明 IRQ 函数
	// IRQ:中断请求(Interrupt Request)
	IRQ(0);		// 电脑系统计时器
	IRQ(1); 		// 键盘
	IRQ(2); 		// 与 IRQ9 相接，MPU-401 MD 使用
	IRQ(3); 		// 串口设备
	IRQ(4); 		// 串口设备
	IRQ(5); 		// 建议声卡使用
	IRQ(6); 		// 软驱传输控制使用
	IRQ(7); 		// 打印机传输控制使用
	IRQ(8); 		// 即时时钟
	IRQ(9); 		// 与 IRQ2 相接，可设定给其他硬件
	IRQ(10); 		// 建议网卡使用
	IRQ(11); 		// 建议 AGP 显卡使用
	IRQ(12); 		// 接 PS/2 鼠标，也可设定给其他硬件
	IRQ(13); 		// 协处理器使用
	IRQ(14); 		// IDE0 传输控制使用
	IRQ(15); 		// IDE1 传输控制使用
}


