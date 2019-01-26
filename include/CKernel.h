#pragma once
#include "CModule.h"
#include "CModManager.h"

class CKernel : public CModule {
public:
    CKernel();
    virtual ~CKernel();
public:
    virtual bool init();
public:
    CModManager mods;
}kernel;
