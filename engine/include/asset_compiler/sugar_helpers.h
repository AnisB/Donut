#pragma once

// Internal includes
#include <resource/sugar_descriptor.h>

namespace donut
{
	bool read_sugar(const char* target_path, TSugarDescriptor& output_sugar);
}