#pragma once
#include "types.h"

namespace debug {
    // 初始化 Debug 信息
    void init_debug(MULTIBOOT *mb);

    // 打印当前的函数调用栈信息
    void panic(const char *msg);

    // 打印当前的段存器值
    void print_cur_status();
}
