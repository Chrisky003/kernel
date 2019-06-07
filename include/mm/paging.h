#pragma once
#include "stdlib.h"

namespace paging {
    // reference from libsystem.
    // the bitmap of the available page is
    // in a specific location, usually 0x500400(ends at 0x540400).
    // and the PDE etc.. are at 0x100000.
    void init();
    void malloc_page();
    struct PTE {
        int flag_addr_and_zero;
            // bit 0 is 1 or 0 depends on whether the PTE is present.
            // bit 7(G)(reference from intel manual).
            // 8:11 are zero(exactly ignored).
    };
    struct PDE{                  
        int flag_addr_and_zero;
            // bit 0 is 1 or 0 depends on whether the PTE is present.
            // bit 7 is always 0.
            // 8:11 are zero(exactly ignored).
    };
    struct CR3 {  
        int flag_addr_and_zero; 
            // 0:2 and 5:11 are zero(exactly ignored).
    };
    extern PDE pd[1024];
    extern PTE pt[1024][1024];
}