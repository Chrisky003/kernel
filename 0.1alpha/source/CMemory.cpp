#include "CMemory.h"
#include "io.h"
using namespace io;

CMemory::CMemory(multiboot_t *mb) {
	this->mb = mb;
}

CMemory::~CMemory() {

}

// 全局描述符表构造函数，根据下标构造
// 参数分别是 数组下标、基地址、限长、访问标志，其它访问标志
/* 结构体定义如下：
typedef struct {
	uint16_t limit_low;	 // 段界限   15～0
	uint16_t base_low;	  // 段基地址 15～0
	uint8_t  base_middle;   // 段基地址 23～16
	uint8_t  access;		// 段存在位、描述符特权级、描述符类型、描述符子类别
	uint8_t  granularity; 	// 其他标志、段界限 19～16
	uint8_t  base_high;	 // 段基地址 31～24
} __attribute__((packed)) gdt_entry_t;
*/
void CMemory::gdt_set_gate(int num, dword base, dword limit, byte access, byte gran) {
	gdt_entries[num].base_low	 = (base & 0xFFFF);
	gdt_entries[num].base_middle  = (base >> 16) & 0xFF;
	gdt_entries[num].base_high	= (base >> 24) & 0xFF;

	gdt_entries[num].limit_low	= (limit & 0xFFFF);
	gdt_entries[num].granularity  = (limit >> 16) & 0x0F;

	gdt_entries[num].granularity |= gran & 0xF0;
	gdt_entries[num].access	   = access;
}

// 声明内核栈地址
extern dword stack;
extern "C" void gdt_flush(int addr) {
	asm("	mov    0x4(%esp),%eax\n");
	asm("	lgdtl  (%eax)\n");
	asm("	mov    $0x10,%ax\n");
	asm("	mov    %eax,%ds\n");
	asm("	mov    %eax,%es\n");
	asm("	mov    %eax,%fs\n");
	asm("	mov    %eax,%gs\n");
	asm("	mov    %eax,%ss\n");
	asm("	jmp    gdt_flush.flush\n");
	asm("gdt_flush.flush:\n");
	asm("	ret\n");
}

// 初始化全局描述符表
void CMemory::init_gdt() {
	// 全局描述符表界限 e.g. 从 0 开始，所以总长要 - 1
	gdt_ptr.limit = sizeof(gdt_entry_t) * GDT_LENGTH - 1;
	gdt_ptr.base = (dword)&gdt_entries;	
	// 采用 Intel 平坦模型
	gdt_set_gate(0, 0, 0, 0, 0);
	// 按照 Intel 文档要求，第一个描述符必须全 0
	gdt_set_gate(1, 0, 0xFFFFFFFF, 0x9A, 0xCF); 	// 指令段
	gdt_set_gate(2, 0, 0xFFFFFFFF, 0x92, 0xCF); 	// 数据段
	gdt_set_gate(3, 0, 0xFFFFFFFF, 0xFA, 0xCF); 	// 用户模式代码段
	gdt_set_gate(4, 0, 0xFFFFFFFF, 0xF2, 0xCF); 	// 用户模式数据段

	// 加载全局描述符表地址到 GPTR 寄存器
	gdt_flush(memory::pointerToInt(&gdt_ptr));
}

