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

typedef struct multiboot
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