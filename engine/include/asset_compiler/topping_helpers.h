#pragma once

// Internal include
#include "resource/topping_descriptor.h"

namespace donut 
{
	bool read_topping(const char* target_path, TToppingDescriptor& descriptor);
}