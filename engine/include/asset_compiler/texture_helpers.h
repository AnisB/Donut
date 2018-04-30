#pragma once

#include "resource/texture.h"
#include "resource/skybox.h"
 
namespace donut
{
	bool read_texture(const char* path_source, TTexture& output_texture);
	bool read_skybox(const char* path_source, TSkybox& output_skybox);
}