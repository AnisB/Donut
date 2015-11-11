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
	bool CheckFrameBuffer()
	{
		if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
 		{
 			GRAPHICS_ERROR("There is a problem with your gbuffer frame buffer dude "<<glGetError());
 			return true;
 		}
 		return false;
	}

	void ClearBuffer()
	{
 		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}
	 		
	void DeleteFrameBuffers(std::vector<GLuint>& _frameBuffers)
	{
		#if LINUX | WIN32
		glDeleteFramebuffers((GLsizei)_frameBuffers.size(), &_frameBuffers[0]);
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

	void BindToFrameBuffer(const TTextureInfo& _tex)
	{
 		switch(_tex.type)
 		{
			case TTextureNature::COLOR:
			{
				#if LINUX | WIN32
		 		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0+_tex.offset,  GL_TEXTURE_2D, _tex.texID,0);
		 		#endif

		 		#ifdef MACOSX
		 		glFramebufferTextureEXT(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0_EXT+_tex.offset, _tex.texID,0);
		 		#endif
			}
			break;
	 		case TTextureNature::DEPTH:
	 		{
				#if LINUX | WIN32
		 		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, _tex.texID,0);
		 		#endif
		 		
		 		#ifdef MACOSX
		 		glFramebufferTextureEXT(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, _tex.texID, 0);
		 		#endif
	 		}
	 		break;
	 		default:
	 			GRAPHICS_ERROR("Unsuported texture nature "<<_tex.type);
	 	}
	}
	void CreateTexture(TTextureInfo& _tex, int parWidth, int parHeight)
	{
		GRAPHICS_DEBUG("Creating GPU texture");
		glGenTextures(1, &_tex.texID);
		glBindTexture(GL_TEXTURE_2D, _tex.texID);
		if(_tex.type == TTextureNature::COLOR)
		{
			glTexImage2D(GL_TEXTURE_2D, 0,GL_RGBA, parWidth, parHeight, 0,GL_RGBA, GL_FLOAT, 0);
		}
		else if(_tex.type == TTextureNature::DEPTH)
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
		glDeleteTextures((GLsizei)_textures.size(), &_textures[0]);
		#endif
		
		#ifdef MACOSX
		glDeleteTexturesEXT(_textures.size(), &_textures[0]);
		#endif
	}

	void DeleteTexture(TTextureInfo& _tex)
	{
		#if LINUX | WIN32
		glDeleteTextures(1, &_tex.texID);
		#endif
		
		#ifdef MACOSX
		glDeleteTexturesEXT(1, &_tex.texID);
		#endif
	}

	void ReadRGBFrameBuffer(int _width, int _length, unsigned char* _output)
	{
		glReadPixels(0, 0, _width, _length, GL_RGB, GL_UNSIGNED_BYTE, _output);
	}

	TGeometry* CreateGeometry(const TShader& _shader, float* _dataArray, int _numVert, unsigned* _indexArray, int num_faces)
	{
		TGeometry * newModel = new TGeometry();
		glGenVertexArrays (1, &newModel->vertexArray);
		glBindVertexArray (newModel->vertexArray);
		
		glGenBuffers(1, &newModel->vertexBuffer);
		glBindBuffer(GL_ARRAY_BUFFER, newModel->vertexBuffer);
		glBufferData(GL_ARRAY_BUFFER, sizeof(float)*_numVert*8, _dataArray, GL_STATIC_DRAW);

		glGenBuffers(1, &newModel->indexBuffer);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, newModel->indexBuffer);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned)*num_faces*3, _indexArray, GL_STATIC_DRAW);
		GLuint posAtt = glGetAttribLocation(_shader.FProgramID, "position");
		GLuint normalAtt = glGetAttribLocation(_shader.FProgramID, "normal");
		GLuint texCoordAtt = glGetAttribLocation(_shader.FProgramID, "tex_coord");
		glEnableVertexAttribArray (posAtt);
		glEnableVertexAttribArray (normalAtt);
		glEnableVertexAttribArray (texCoordAtt);
		glVertexAttribPointer (posAtt, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glVertexAttribPointer (normalAtt, 3, GL_FLOAT, GL_FALSE, 0, (void*)(sizeof (GLfloat)*_numVert*3));
		glVertexAttribPointer (texCoordAtt, 2, GL_FLOAT, GL_FALSE, 0, (void*)(sizeof (GLfloat)*_numVert*6));
		
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray (0);
		newModel->nbVertices = num_faces*3;
		return newModel;
	}
}
