#include "CModManager.h"

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
    if (moduleVec[index] != NULL) {
        return false;
    }
    else if (module == NULL) {
        return false;
    }
    //else
    moduleVec[index] = module;
    size++;
    return true;
}
