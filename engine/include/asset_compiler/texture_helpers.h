#pragma once

#include "resource/texture.h"
#include "resource/skybox.h"
 
namespace donut
{
	// Fill a texture from a file source
	void LoadTexture(const char* path_source, TTexture& output_texture);

	// Skybox helpers
	void LoadSkybox(const char* path_source, TSkybox& output_skybox);
}