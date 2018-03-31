#pragma once

//Library includes
#include "graphics/geometry.h"
#include "graphics/shader.h"
#include "graphics/shaderdata.h"

// STL includes
#include <vector>

namespace donut
{
	// Generic purpose functions
	bool CheckGLState(bool _clearState = false);

	// Frame buffer functions
	uint32_t CreateFrameBuffer();
	void BindFrameBuffer(uint32_t parFrameBuffer);
	void UnBindFrameBuffer();
	bool CheckFrameBuffer();
	void DeleteFrameBuffers(std::vector<uint32_t>& _frameBuffers);
	void DeleteFrameBuffer(uint32_t& _frameBuffer);
	void BindToFrameBuffer(const TTextureInfo& _tex);
	void ClearBuffer();
	void SetClearColor(const bento::Vector4& _color);

	// Texture creation and deletion
	void CreateTexture(TTextureInfo& _tex, int parWidth, int parHeight);
	void DeleteTextures(std::vector<uint32_t>& _textures);
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