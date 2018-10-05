#pragma once

typedef int dword;
typedef short word;
typedef char byte;
typedef __builtin_va_list va_list;

#define NULL 0
#define va_start(ap, last)		 (__builtin_va_start(ap, last))
#define va_arg(ap, type)		   (__builtin_va_arg(ap, type))
#define va_end(ap)

class POINT
{
public:
	POINT();
	POINT(int x, int y);
public:
	int x,y;
};

typedef struct multiboot_t
{
	int flags;
	// Multiboot 的版本信息
	/**
	* 从 BIOS 获知的可用内存
	*
	* mem_lower 和 mem_upper 分别指出了低端和高端内存的大小,单位是。K
	* 低端内存的首地址是 0 ,高端内存的首地址是 1M 。
	* 低端内存的最大可能值是 640K
	* 高端内存的最大可能值是最大值减去 1M 。但并不保证是这个值。
	*/
	int mem_lower;
	int mem_upper;
	int boot_device;
	int cmdline;
	int mods_count;
	int mods_addr;
	// 指出引导程序从哪个磁盘设备载入的映像BIOSOS
	// 内核命令行
	// boot 模块列表
	/**
	* ELF 格式内核映像的 section 头表。包括每项的大小、一共有几项以及作为名字索引
	* 的字符串。
	*/
	int num;
	int size;
	int addr;
	int shndx;
	/**
	* 以下两项指出保存由 BIOS 提供的内存分布的缓冲区的地址和长度
	* mmap_addr 是缓冲区的地址, mmap_length 是缓冲区的总大小
	* 缓冲区由一个或者多个下面的 mmap_entry_t 组成
	*/
	int mmap_length;
	int mmap_addr;
	int drives_length;
	int drives_addr;
	int config_table;
	int boot_loader_name;
	int apm_table;
	int vbe_control_info;
	int vbe_mode_info;
	int vbe_mode;
	int vbe_interface_seg;
	int vbe_interface_off;
	int vbe_interface_len;
} __attribute__((packed)) multiboot_t;

// 全局描述符类型
typedef
struct gdt_entry_t {
	word limit_low;	 // 段界限   15～0
	word base_low;	  // 段基地址 15～0
	byte  base_middle;   // 段基地址 23～16
	byte  access;		// 段存在位、描述符特权级、描述符类型、描述符子类别
	byte  granularity; 	// 其他标志、段界限 19～16
	byte  base_high;	 // 段基地址 31～24
} __attribute__((packed)) gdt_entry_t;

// GDTR
typedef
struct gdt_ptr_t {
	word limit; 	// 全局描述符表限长
	dword base; 		// 全局描述符表 32位 基地址
} __attribute__((packed)) gdt_ptr_t;

// ELF 格式区段头
typedef
struct elf_section_header_t {
	dword name;
	dword type;
	dword flags;
	dword addr;
	dword offset;
	dword size;
	dword link;
	dword info;
	dword addralign;
	dword entsize;
} __attribute__((packed)) elf_section_header_t;

// ELF 格式符号
typedef
struct elf_symbol_t {
	dword name;
	dword value;
	dword size;
	byte  info;
	byte  other;
	word shndx;
} __attribute__((packed)) elf_symbol_t;

// ELF 信息
typedef
struct elf_t {
	elf_symbol_t *symtab;
	dword	  symtabsz;
	const char   *strtab;
	dword	  strtabsz;
} elf_t;
