#pragma once

// Internal includes
#include "resource/texture.h"
 
namespace donut
{
	bool read_texture(const char* path_source, TTexture& output_texture);
}