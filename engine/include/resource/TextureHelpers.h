#pragma once

#include "Texture.h"
 
namespace donut
{
	namespace TextureHelpers
	{
		// Img helpers
	    STRING_TYPE ImgTypeToString(TImgType::Type parType);
		TImgType::Type GetImgType(const STRING_TYPE & parImg);

		// Texture helpers
	 	TTexture * LoadTexture(const STRING_TYPE & parImg);

	 	// Skybox helpers
	 	TSkyboxTexture* LoadSkybox(const STRING_TYPE& _location, TImgType::Type _type);

	 	// GPU to CPU methods
	 	void TakeScreenShot(const STRING_TYPE& parFileName);
	    void SaveTextureToFile(const STRING_TYPE& parFileName, const TTexture * parTexture);
	}
}