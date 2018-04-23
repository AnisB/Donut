#pragma once

// Internal includes
#include "resource/egg.h"

namespace donut
{
	bool write_egg(const char* egg_path, const TEgg& source_egg);
	bool read_egg(const char* egg_path, TEgg& output_egg);
}