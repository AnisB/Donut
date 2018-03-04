/**
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as
 * published by the Free Software Foundation, either version 3 of the
 * License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 *
 **/



#ifndef TEXTURE_HELPERS
#define TEXTURE_HELPERS

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
	 	void CreateTexture(TTexture* parTex);

	 	// Skybox helpers
	 	TSkyboxTexture* LoadSkybox(const STRING_TYPE& _location, TImgType::Type _type);
	 	void CreateSkybox(TSkyboxTexture* _skyboxTex);

	 	// Other
	 	GLuint CreateTextureCube();
	    void CreateDataTexture(TTexture* parTex);
	    void ReLoadTexture(TTexture* parTex);

	 	void BindToCubeMap(GLuint parType, TTexture* parTexture);

	 	// GPU to CPU methods
	 	void TakeScreenShot(const STRING_TYPE& parFileName);
	    void SaveTextureToFile(const STRING_TYPE& parFileName, const TTexture * parTexture);
	}
}

#endif // TEXTURE_HELPERS