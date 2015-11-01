#ifndef RENDER_HELPER
#define RENDER_HELPER

#include "graphics/common.h"

void CheckGLState(const std::string& desc);
GLuint CreateFrameBuffer();
void BindFrameBuffer(GLuint parFrameBuffer);
void UnBindFrameBuffer();
namespace TextureNature
{
	enum Type
	{
		COLOR,
		DEPTH
	};
};
void CreateTexture(GLuint& parTex, int parWidth, int parHeight, TextureNature::Type parType);
void BindToFrameBuffer(GLuint parTextureIndex, TextureNature::Type parTextureType, GLuint parOffset = 0);


#endif // RENDER_HELPER