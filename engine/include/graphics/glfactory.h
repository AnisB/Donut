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
#include "graphics/geometry.h"
#include "graphics/shader.h"
#include "graphics/shaderdata.h"
#include "base/platform.h"

// STL includes
#include <vector>

namespace donut
{
	// Generic purpose functions
	bool CheckGLState(bool _clearState = false);

	// Frame buffer functions
	GLuint CreateFrameBuffer();
	void BindFrameBuffer(GLuint parFrameBuffer);
	void UnBindFrameBuffer();
	bool CheckFrameBuffer();
	void DeleteFrameBuffers(std::vector<GLuint>& _frameBuffers);
	void DeleteFrameBuffer(GLuint& _frameBuffer);
	void BindToFrameBuffer(const TTextureInfo& _tex);
	void ClearBuffer();
	void SetClearColor(const bento::Vector4& _color);

	// Texture creation and deletion
	void CreateTexture(TTextureInfo& _tex, int parWidth, int parHeight);
	void DeleteTextures(std::vector<GLuint>& _textures);
	void DeleteTexture(TTextureInfo& _tex);

	// Reading from currentFrameBuffer
	void ReadRGBFrameBuffer(int _width, int _length, unsigned char* _output);

	// Creates a geometry into the GPU
	TGeometry* CreateGeometry(const TShader& _shader, float* _dataArray, int _numVert, unsigned* _indexArray, int num_faces);

#if 0
	#define GL_API_CHECK_START() {assert_msg_NO_RELEASE(CheckGLState(), "GL error at the start of "<<FUNCTION_NAME)}
	#define GL_API_CHECK_MIDDLE() {assert_msg_NO_RELEASE(CheckGLState(), "GL error at the middle of "<<FUNCTION_NAME)}
	#define GL_API_CHECK_END() {assert_msg_NO_RELEASE(CheckGLState(), "GL error at the end of "<<FUNCTION_NAME)}
#else
	#define GL_API_CHECK_START() {}
	#define GL_API_CHECK_MIDDLE() {}
	#define GL_API_CHECK_END() {}
#endif // _DEBUG
}


#endif // GL_FACTORY_GRAPHICS_DONUT