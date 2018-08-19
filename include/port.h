#pragma once
#include "def.h"

namespace port
{
	inline void out8(word port, byte value);
	inline byte in8(word port);
	inline short in16(word port);
}
