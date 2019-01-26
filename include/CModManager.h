#pragma once
#include "string.h"
#include "CModule.h"
#include "types.h"

class CModManager{
public:
	CModManager();
public:
	bool addMod(CModule *module);
	bool addMod(int index, CModule *module);
public:
	int size;
	CModule *moduleVec[1024];
};
