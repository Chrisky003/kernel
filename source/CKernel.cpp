#include "CKernel.h"

CKernel::CKernel() {
    mods.addMod(this);
}

CKernel::~CKernel() {

}

bool CKernel::init() {
    return true;
}