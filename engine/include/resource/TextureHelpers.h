#pragma once

#include "Texture.h"
 
namespace donut
{
	// Fill a texture from a file source
	void LoadTexture(const char* path_source, TTexture& output_texture);

	// Skybox helpers
	void LoadSkybox(const char* path_source, TSkyboxTexture& output_skybox);
}