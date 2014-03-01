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
 
namespace TextureHelpers
{
    std::string ImgTypeToString(TImgType::Type parType);
	TImgType::Type GetImgType(const std::string & parImg);
 	TTexture * LoadTexture(const std::string & parImg);
 	GLuint CreateTextureCube();
 	void CreateTexture(TTexture* parTex);
    void CreateDataTexture(TTexture* parTex);

 	void BindToCubeMap(GLuint parType, TTexture* parTexture);

 	void TakeScreenShot(const std::string& parFileName);
}

#endif // TEXTURE_HELPERS
