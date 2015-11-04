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

#ifndef GL_FACTORY_GRAPHICS_DONUT
#define GL_FACTORY_GRAPHICS_DONUT

//Library includes
#include "graphics/common.h"
// STL includes
#include <vector>

namespace Donut
{
	// Generic purpose functions
	void CheckGLState(const std::string& desc);

	// Frame buffer functions
	GLuint CreateFrameBuffer();
	void BindFrameBuffer(GLuint parFrameBuffer);
	void UnBindFrameBuffer();
	void DeleteFrameBuffers(std::vector<GLuint>& _frameBuffers);
	void DeleteFrameBuffer(GLuint& _frameBuffer);

	// Should be moved to texture when it will be refactored
	namespace TextureNature 
	{
		enum Type
		{
			COLOR,
			DEPTH
		};
	};
	void BindToFrameBuffer(GLuint parTextureIndex, TextureNature::Type parTextureType, GLuint parOffset = 0);

	// Texture creation and deletion
	void CreateTexture(GLuint& parTex, int parWidth, int parHeight, TextureNature::Type parType);
	void DeleteTextures(std::vector<GLuint>& _textures);
	void DeleteTexture(GLuint& _tex);

	// Reading from currentFrameBuffer
	void ReadRGBFrameBuffer(int _width, int _length, unsigned char* _output);
}


#endif // GL_FACTORY_GRAPHICS_DONUT