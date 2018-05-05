#pragma once

// Internal includes
#include "resource/flour_descriptor.h"

namespace donut
{
	bool read_flour(const char* file_name, TFlourDescriptor& _output);
}