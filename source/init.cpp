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
    void (**ps)(void);
    ps = &__KERNEL__CTOR__LIST__;
    for (int i = 0; ps[i] != __KERNEL__CTOR__END__; i++) {
        ps[i]();
    }
    return;
}

extern "C" void fini() {
    void (**ps)(void);
    ps = &__KERNEL__DTOR__LIST__;
    for (int i = 0; ps[i] != __KERNEL__DTOR__END__; i++) {
        ps[i]();
    }
    return;
}
