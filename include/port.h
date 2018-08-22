#pragma once
#include "def.h"

namespace port
{
	void out8(word port, byte value);
	byte in8(word port);
	short in16(word port);
}
