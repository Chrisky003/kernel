#include "CKernel.h"

CKernel kernel;

CKernel::CKernel(): CModule(0) {
    
}

CKernel::~CKernel() {

}

bool CKernel::init() {
    return true;
}