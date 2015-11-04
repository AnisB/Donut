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

#include "glfactory.h"
#include "base/common.h"

namespace Donut
{
	void CheckGLState(const std::string& desc)
	{
		GLenum e = glGetError();
		if(desc == FLUSH_GL_ERROR)
			return;
		if (e != GL_NO_ERROR) 
		{
			GRAPHICS_ERROR("OpenGL error in: "<<desc.c_str()<<" "<<e);
		}
		else
		{
			GRAPHICS_DEBUG("No OpenGL errors@"<<desc);
		}
	}

	GLuint CreateFrameBuffer()
	{
		GLuint frameBufferIndex;
		#if LINUX | WIN32
		glGenFramebuffers(1, &frameBufferIndex);
		#endif
		#ifdef MACOSX 
		glGenFramebuffersEXT(1, &frameBufferIndex);
		#endif
		return frameBufferIndex;
	}
	void BindFrameBuffer(GLuint parFrameBuffer)
	{
		#if LINUX | WIN32
		glBindFramebuffer(GL_FRAMEBUFFER, parFrameBuffer);
		#endif
		#ifdef MACOSX
		glBindFramebufferEXT(GL_FRAMEBUFFER, parFrameBuffer);
		#endif
	}

	void UnBindFrameBuffer()
	{
		#if LINUX | WIN32
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		#endif
		
		#ifdef MACOSX
		glBindFramebufferEXT(GL_FRAMEBUFFER, 0);
		#endif
	}

	void DeleteFrameBuffers(std::vector<GLuint>& _frameBuffers)
	{
		#if LINUX | WIN32
		glDeleteFramebuffers(_frameBuffers.size(), &_frameBuffers[0]);
		#endif
		
		#ifdef MACOSX
		glDeleteFramebuffersEXT(_frameBuffers.size(), &_frameBuffers[0]);
		#endif
	}

	void DeleteFrameBuffer(GLuint& _frameBuffer)
	{
		#if LINUX | WIN32
		glDeleteFramebuffers(1, &_frameBuffer);
		#endif
		
		#ifdef MACOSX
		glDeleteFramebuffersEXT(1, &_frameBuffer);
		#endif
	}

	void BindToFrameBuffer(GLuint parTextureIndex, TextureNature::Type parTextureType, GLuint parOffset)
	{
	 		if(parTextureType == TextureNature::COLOR)
			{
				#if LINUX | WIN32
		 		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0+parOffset,  GL_TEXTURE_2D, parTextureIndex,0);
		 		#endif

		 		#ifdef MACOSX
		 		glFramebufferTextureEXT(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0_EXT+parOffset, parTextureIndex,0);
		 		#endif
			}
	 		else if(parTextureType == TextureNature::DEPTH)
	 		{
				#if LINUX | WIN32
		 		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, parTextureIndex,0);
		 		#endif
		 		
		 		#ifdef MACOSX
		 		glFramebufferTextureEXT(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, parTextureIndex, 0);
		 		#endif
	 		}

	}
	void CreateTexture(GLuint& parTex, int parWidth, int parHeight, TextureNature::Type parType)
	{
		GRAPHICS_DEBUG("Creating GPU texture");
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
		GRAPHICS_DEBUG("GPU texture created...");
	}

	void DeleteTextures(std::vector<GLuint>& _textures)
	{
		#if LINUX | WIN32
		glDeleteTextures(_textures.size(), &_textures[0]);
		#endif
		
		#ifdef MACOSX
		glDeleteTexturesEXT(_textures.size(), &_textures[0]);
		#endif
	}

	void DeleteTexture(GLuint& _tex)
	{
		#if LINUX | WIN32
		glDeleteTextures(1, &_tex);
		#endif
		
		#ifdef MACOSX
		glDeleteTexturesEXT(1, &_tex);
		#endif
	}

	void ReadRGBFrameBuffer(int _width, int _length, unsigned char* _output)
	{
		glReadPixels(0, 0, _width, _length, GL_RGB, GL_UNSIGNED_BYTE, _output);
	}
}
