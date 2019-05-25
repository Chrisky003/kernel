#pragma once
#include "types.h"

namespace memManage {
    typedef
    struct gdt_entry_t {
        uint16 limit_low;     // 段界限15 ~ 0
        uint16 base_low;      // 段基地址 15 ~ 0
        uint8 base_middle;    // 段基地址 23 ~ 16
        uint8 access;         // 段存在位、描述符特权级、描述符类型、描述符子类别
        uint8 granularity;    // 其他标志、段界限 19 ~ 16
        uint8 base_high;      // 段基地址 31 ~ 24
    } __attribute__((packed)) GDT_ENTRY;

    // GDTR
    typedef
    struct gdt_ptr_t {
        uint16 limit;     // 全局描述符表限长
        uint32 base;      // 全局描述符表 32 位基地址
    } __attribute__((packed)) GDT_PTR;

    void init_mm();
}