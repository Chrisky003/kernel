#include "CModManager.h"

CModManager modManager;

CModManager::CModManager(): size(0) {
    lib::string::memset(moduleVec, 0, 1024 * sizeof(CModule));
}
bool CModManager::addMod(CModule *module) {
    if (size >= 1024) {
        return false;
    }
    else if (module == NULL) {
        return false;
    }
    //else
    moduleVec[size] = module;
    size++;
    return true;
}
bool CModManager::addMod(int index, CModule *module) {
    if (module == NULL) {
        return false;
    }
    else if (moduleVec[index] != NULL) {
        addMod(moduleVec[index]);
        // moduleVec[index] = module;
    }
    //else
    moduleVec[index] = module;
    size++;
    return true;
}

bool CModManager::init() {
    bool ret(true);
    for (int i(0); i < size && ret; i++) {
        if(moduleVec[i] != NULL) {
            ret = moduleVec[i]->init();
        }
    }
    return ret;
}