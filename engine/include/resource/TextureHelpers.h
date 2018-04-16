#pragma once

#include "Texture.h"
 
namespace donut
{
	// Fill a texture from a file source
	void LoadTexture(const char* path_source, TTexture& output_texture);

	// Skybox helpers
	TSkyboxTexture* LoadSkybox(const STRING_TYPE& skybox_source);

	// GPU to CPU methods
	void TakeScreenShot(const STRING_TYPE& parFileName);
	void SaveTextureToFile(const STRING_TYPE& parFileName, const TTexture * parTexture);
}