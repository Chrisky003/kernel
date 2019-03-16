#pragma once
// #include "CModManager.h"

class CModManager;
extern CModManager modManager;

#define MODULE_PRIORITY(p) 

class CModule {
public:
    CModule(CModManager *pmodManager = &modManager);
    CModule(int index, CModManager *pmodManager = &modManager);
    virtual ~CModule() = 0;
public:
    virtual bool init() = 0;
};