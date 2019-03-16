#include "CModule.h"
#include "CModManager.h"
#include "io.h"

CModule::CModule(CModManager *pmodManager) {
    pmodManager->addMod(this);
    io::console::real::printk("module:0x%x\n", this);
}

CModule::CModule(int index, CModManager *pmodManager) {
    pmodManager->addMod(index, this);
    io::console::real::printk("module:0x%x, index:%d\n", this, index);
}

CModule::~CModule() {
    
}