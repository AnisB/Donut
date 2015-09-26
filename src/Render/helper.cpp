#include "helper.h"

#include <base/common.h>

void CheckGLState(const std::string& desc)
{
	if(desc=="FLUSH")
		return;
	GLenum e = glGetError();
	if (e != GL_NO_ERROR) 
	{
		RENDER_ERROR("OpenGL error in: "<<desc.c_str()<<" "<<e);
	}
	else
	{
		RENDER_DEBUG("No OpenGL errors@"<<desc);
	}
}

GLuint CreateFrameBuffer()
{
	GLuint frameBufferIndex;
	#ifdef LINUX
	glGenFramebuffers(1, &frameBufferIndex);
	#endif
	#ifdef MACOSX
	glGenFramebuffersEXT(1, &frameBufferIndex);
	#endif
	return frameBufferIndex;
}
void BindFrameBuffer(GLuint parFrameBuffer)
{
	#ifdef LINUX
	glBindFramebuffer(GL_FRAMEBUFFER, parFrameBuffer);
	#endif
	#ifdef MACOSX
	glBindFramebufferEXT(GL_FRAMEBUFFER, parFrameBuffer);
	#endif
}

void UnBindFrameBuffer()
{
	#ifdef LINUX
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	#endif
	
	#ifdef MACOSX
	glBindFramebufferEXT(GL_FRAMEBUFFER, 0);
	#endif
}

void BindToFrameBuffer(GLuint parTextureIndex, TextureNature::Type parTextureType, GLuint parOffset)
{
 		if(parTextureType == TextureNature::COLOR)
		{
			#ifdef LINUX
	 		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0+parOffset,  GL_TEXTURE_2D, parTextureIndex,0);
	 		#endif

	 		#ifdef MACOSX
	 		glFramebufferTextureEXT(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0_EXT+parOffset, parTextureIndex,0);
	 		#endif
		}
 		else if(parTextureType == TextureNature::DEPTH)
 		{
	 		#ifdef LINUX
	 		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, parTextureIndex,0);
	 		#endif
	 		
	 		#ifdef MACOSX
	 		glFramebufferTextureEXT(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, parTextureIndex, 0);
	 		#endif
 		}

}

void CreateTexture(GLuint& parTex, int parWidth, int parHeight, TextureNature::Type parType)
{
	glGenTextures(1, &parTex);
	glBindTexture(GL_TEXTURE_2D, parTex);
	if(parType == TextureNature::COLOR)
	{
		glTexImage2D(GL_TEXTURE_2D, 0,GL_RGBA, parWidth, parHeight, 0,GL_RGBA, GL_FLOAT, 0);
	}
	else if(parType == TextureNature::DEPTH)
	{
		glTexImage2D(GL_TEXTURE_2D,0, GL_DEPTH_COMPONENT24, parWidth, parHeight, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
	}

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glBindTexture(GL_TEXTURE_2D, 0);
}