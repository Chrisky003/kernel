#pragma once

#ifndef NULL
	#define NULL 0
#endif

#ifndef TRUE
	#define TRUE 1
#endif
#ifndef FALSE
	#define FALSE 0
#endif

typedef	unsigned	int		uint32;
typedef	signed		int		int32;
typedef	unsigned	short	uint16;
typedef signed		short	int16;
typedef	unsigned	char	uint8;
typedef	signed		char	int8;
typedef __builtin_va_list va_list;

#define va_start(ap, last)         (__builtin_va_start(ap, last))
#define va_arg(ap, type)           (__builtin_va_arg(ap, type))
#define va_end(ap) 

class POINT {
public:
	int x;
	int y;
	POINT() {
		this->x = this->y = 0;
	}
	POINT(int x, int y) {
		this->x = x;
		this->y = y;
	}
};

typedef struct MULTIBOOT
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
} __attribute__((packed)) MULTIBOOT;

#define ELF32_ST_TYPE(i) ((i)&0xf)

namespace lib::elf {
	// ELF 格式区段头
	typedef
	struct ELF_SECTION_HEADER {
	uint32 name;
	uint32 type;
	uint32 flags;
	uint32 addr;
	uint32 offset;
	uint32 size;
	uint32 link;
	uint32 info;
	uint32 addralign;
	uint32 entsize;
	} __attribute__((packed)) ELF_SECTION_HEADER;

	// ELF 格式符号
	typedef
	struct ELF_SYMBOL {
	uint32 name;
	uint32 value;
	uint32 size;
	uint8  info;
	uint8  other;
	uint16 shndx;
	} __attribute__((packed)) ELF_SYMBOL;

	// ELF 信息
	typedef
	struct ELF {
	ELF_SYMBOL *symtab;
	uint32      symtabsz;
	const char   *strtab;
	uint32      strtabsz;
	} ELF;
}

#define assert(x, info)                                       	\
	do {                                                	\
		if (!(x)) {                                     \
			panic(info); 		     		\
		}                                               \
	} while (0)

// 编译期间静态检测
#define static_assert(x)                                	\
	switch (x) { case 0: case (x): ; }
