#pragma once

// Internal includes
#include "resource/shader_source.h"

namespace donut
{
	bool read_shader_source(const char* target_path, TShaderSource& output_shader);
}