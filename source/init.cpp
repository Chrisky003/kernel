#include "types.h"

void (*__KERNEL__CTOR__LIST__)();
void (*__KERNEL__CTOR__END__)();
void (*__KERNEL__DTOR__LIST__)();
void (*__KERNEL__DTOR__END__)();
extern "C" int kernelEntry(MULTIBOOT *pmultiboot);
extern "C" void init();
extern "C" void fini();

extern "C" void _start(MULTIBOOT *pmultiboot) {
    init();
    kernelEntry(pmultiboot);
    fini();
    return;
}

extern "C" void init() {
    union {
        void (*pf)();
        int data;
    } uni;
    for (uni.pf = __KERNEL__CTOR__LIST__; uni.pf != __KERNEL__CTOR__END__; uni.data += 4) {
        uni.pf();
    }
    return;
}

extern "C" void fini() {
    union {
        void (*pf)();
        int data;
    } uni;
    for (uni.pf = __KERNEL__DTOR__LIST__; uni.pf != __KERNEL__DTOR__END__; uni.data += 4) {
        uni.pf();
    }
    return;
}
