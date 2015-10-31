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


 #include "FrameCanvas.h"
 #include "render/defines.h"
 #include "render/common.h"
 #include "render/helper.h"

 #include <base/common.h>
 #include <multiThread/defines.h>


namespace Donut
{
	#define CANVAS_VERTEX_SHADER "shaders/canvas/vertex.glsl"
	#define CANVAS_FRAGMENT_SHADER "shaders/canvas/fragment.glsl"

	GLfloat fullScreenQuad[20] = { 
		-1.0f, -1.0f, 0.0f, 
		-1.0f, 1.0f, 0.0f, 
		1.0f, -1.0f, 0.0f, 
		1.0f, 1.0f, 0.0f, 
		0.0,0.0,
		0.0,1.0,
		1.0,0.0,
		1.0,1.0,
	};
 	TFrameCanvas::TFrameCanvas()
 	: TDrawableObject()
	, FFrameBuffer(0)
	, FAlbedoBuffer(0)
	, FDepthBuffer(0)
	, FNormalBuffer(0)
	, FSpecularBuffer(0)
 	, FShader(0,CANVAS_VERTEX_SHADER, BASIC_SHADER, BASIC_SHADER, BASIC_SHADER, CANVAS_FRAGMENT_SHADER)
 	, FCanvasType(FrameCanvasContent::STANDARD)
 	, FTextureCounter(0)
 	{

 	}

 	TFrameCanvas::~TFrameCanvas()
 	{
 	}

	void TFrameCanvas::createShader()
	{
 		ShaderManager::Instance().CreateShader(FShader);
	}

	void TFrameCanvas::createVAO()
	{
 		// Full screen quad VAO
		glGenVertexArrays (1, &FVertexArrayID);
		glBindVertexArray (FVertexArrayID);
		
		glGenBuffers(1, &FVBO);
		glBindBuffer(GL_ARRAY_BUFFER, FVBO);

		glBufferData(GL_ARRAY_BUFFER, sizeof(fullScreenQuad), fullScreenQuad, GL_STATIC_DRAW);
		GLuint posAtt = glGetAttribLocation(FShader.FProgramID, "position");
		GLuint texCoordAtt = glGetAttribLocation(FShader.FProgramID, "tex_coord");
		glEnableVertexAttribArray (posAtt);
		glEnableVertexAttribArray (texCoordAtt);
		glVertexAttribPointer (posAtt, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glVertexAttribPointer (texCoordAtt, 2, GL_FLOAT, GL_FALSE, 0, (void*)(sizeof (GLfloat)*12));
		
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray (0);
	}

	void TFrameCanvas::Init()
 	{
 		createShader();
		createVAO();

		// Generation du buffer
		FFrameBuffer = CreateFrameBuffer();
		BindFrameBuffer(FFrameBuffer);
		RENDER_DEBUG("Frame buffer init "<<FFrameBuffer);
		if(FCanvasType==FrameCanvasContent::STANDARD)
		{
	 		CreateTexture(FAlbedoBuffer, DEFAULT_WIDTH, DEFAULT_LENGHT, TextureNature::COLOR);
	 		BindToFrameBuffer(FAlbedoBuffer, TextureNature::COLOR, 0);

	 		CreateTexture(FDepthBuffer, DEFAULT_WIDTH, DEFAULT_LENGHT, TextureNature::DEPTH);
	 		BindToFrameBuffer(FDepthBuffer, TextureNature::DEPTH, 0);

	 		if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
	 		{
	 			RENDER_ERROR("There is a problem with your standard frame buffer dude "<<glGetError());
	 		}

	 		UnBindFrameBuffer();
			RENDER_DEBUG("Frame canvas created");
			
	 		ShaderManager::Instance().EnableShader(FShader);
	 		ShaderManager::Instance().InjectInt(FShader, DEFAULT_WIDTH, "width");
	 		ShaderManager::Instance().InjectInt(FShader, DEFAULT_LENGHT, "lenght");

	 		ShaderManager::Instance().InjectTex(FShader, FAlbedoBuffer, "canvas", 0 );
	 		ShaderManager::Instance().InjectTex(FShader, FDepthBuffer, "depth", 1 );
	 		FTextureCounter = 2;
	 		ShaderManager::Instance().DisableShader();
		}
		else if (FCanvasType==FrameCanvasContent::GBUFFER)
		{
	 		CreateTexture(FAlbedoBuffer, DEFAULT_WIDTH, DEFAULT_LENGHT, TextureNature::COLOR);
	 		BindToFrameBuffer(FAlbedoBuffer, TextureNature::COLOR, 0);

	 		CreateTexture(FNormalBuffer, DEFAULT_WIDTH, DEFAULT_LENGHT, TextureNature::COLOR);
	 		BindToFrameBuffer(FNormalBuffer, TextureNature::COLOR, 1);

	 		CreateTexture(FSpecularBuffer, DEFAULT_WIDTH, DEFAULT_LENGHT, TextureNature::COLOR);
	 		BindToFrameBuffer(FSpecularBuffer, TextureNature::COLOR, 2);

	 		CreateTexture(FPosBuffer, DEFAULT_WIDTH, DEFAULT_LENGHT, TextureNature::COLOR);
	 		BindToFrameBuffer(FPosBuffer, TextureNature::COLOR, 3);

	 		CreateTexture(FDepthBuffer, DEFAULT_WIDTH, DEFAULT_LENGHT, TextureNature::DEPTH);
	 		BindToFrameBuffer(FDepthBuffer, TextureNature::DEPTH, 0);
	 		FTextureCounter = 4;

	 		if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
	 		{
	 			RENDER_ERROR("There is a problem with your standard frame buffer dude "<<glGetError());
	 		}

	 		UnBindFrameBuffer();
			RENDER_DEBUG("Frame canvas created");
			
	 		ShaderManager::Instance().EnableShader(FShader);
	 		ShaderManager::Instance().InjectInt(FShader, DEFAULT_WIDTH, "width");
	 		ShaderManager::Instance().InjectInt(FShader, DEFAULT_LENGHT, "lenght");

	 		ShaderManager::Instance().InjectTex(FShader, FAlbedoBuffer, "canvas", 0 );
	 		ShaderManager::Instance().InjectTex(FShader, FAlbedoBuffer, "nbuffer", 1 );
	 		ShaderManager::Instance().InjectTex(FShader, FAlbedoBuffer, "specbuffer", 2 );
	 		ShaderManager::Instance().InjectTex(FShader, FAlbedoBuffer, "posbuffer", 3 );
	 		ShaderManager::Instance().InjectTex(FShader, FDepthBuffer, "depth", 4 );
	 		ShaderManager::Instance().DisableShader();
		}
		else if (FCanvasType==FrameCanvasContent::DEFFERED)
		{
	 		CreateTexture(FAlbedoBuffer, DEFAULT_WIDTH, DEFAULT_LENGHT, TextureNature::COLOR);
	 		BindToFrameBuffer(FAlbedoBuffer, TextureNature::COLOR, 0);

	 		CreateTexture(FNormalBuffer, DEFAULT_WIDTH, DEFAULT_LENGHT, TextureNature::COLOR);
	 		BindToFrameBuffer(FNormalBuffer, TextureNature::COLOR, 1);

	 		CreateTexture(FSpecularBuffer, DEFAULT_WIDTH, DEFAULT_LENGHT, TextureNature::COLOR);
	 		BindToFrameBuffer(FSpecularBuffer, TextureNature::COLOR, 2);

	 		CreateTexture(FPosBuffer, DEFAULT_WIDTH, DEFAULT_LENGHT, TextureNature::COLOR);
	 		BindToFrameBuffer(FPosBuffer, TextureNature::COLOR, 3);

	 		CreateTexture(FDepthBuffer, DEFAULT_WIDTH, DEFAULT_LENGHT, TextureNature::DEPTH);
	 		BindToFrameBuffer(FDepthBuffer, TextureNature::DEPTH, 0);

	 		FTextureCounter = 4;

	 		if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
	 		{
	 			RENDER_ERROR("There is a problem with your gbuffer frame buffer dude "<<glGetError());
	 		}

	 		UnBindFrameBuffer();
			RENDER_DEBUG("Frame gbuffer canvas created");
			
			FSecondFrameBuffer = CreateFrameBuffer();
			BindFrameBuffer(FSecondFrameBuffer);

	 		CreateTexture(FFinalBuffer, DEFAULT_WIDTH, DEFAULT_LENGHT, TextureNature::COLOR);
	 		BindToFrameBuffer(FFinalBuffer, TextureNature::COLOR, 0);

	 		if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
	 		{
	 			RENDER_ERROR("There is a problem with your gbuffer frame buffer dude "<<glGetError());
	 		}

	 		UnBindFrameBuffer();
	 		ShaderManager::Instance().EnableShader(FShader);
	 		ShaderManager::Instance().InjectInt(FShader, DEFAULT_WIDTH, "width");
	 		ShaderManager::Instance().InjectInt(FShader, DEFAULT_LENGHT, "lenght");

	 		ShaderManager::Instance().InjectTex(FShader, FFinalBuffer, "canvas", 0 );
	 		ShaderManager::Instance().InjectTex(FShader, FAlbedoBuffer, "diff", 1 );
	 		ShaderManager::Instance().InjectTex(FShader, FDepthBuffer, "depth", 2 );
	 		ShaderManager::Instance().InjectTex(FShader, FPosBuffer, "posbuffer", 3 );
	 		ShaderManager::Instance().DisableShader();

		}

 	}

	void TFrameCanvas::SetFragmentShader(const std::string& parFShader)
	{
		FShader.FFragmentShader = parFShader;

	}

	void TFrameCanvas::SetVertexShader(const std::string& parVShader)
	{
		FShader.FVertexShader = parVShader;
	}	

	void TFrameCanvas::InjectData(const TShader& parShader)
	{
		if(FCanvasType==FrameCanvasContent::DEFFERED)
		{
	 		ShaderManager::Instance().EnableShader(parShader);
	 		ShaderManager::Instance().InjectInt(parShader, DEFAULT_WIDTH, "width");
	 		ShaderManager::Instance().InjectInt(parShader, DEFAULT_LENGHT, "lenght");

	 		ShaderManager::Instance().InjectTex(parShader, FAlbedoBuffer, "canvas", 0 );
	 		ShaderManager::Instance().InjectTex(parShader, FNormalBuffer, "nbuffer", 1 );
	 		ShaderManager::Instance().InjectTex(parShader, FSpecularBuffer, "specbuffer", 2 );
	 		ShaderManager::Instance().InjectTex(parShader, FPosBuffer, "posbuffer", 3 );
	 		ShaderManager::Instance().InjectTex(parShader, FDepthBuffer, "depth", 4 );
	 		ShaderManager::Instance().DisableShader();		
		}

	}	

 	void TFrameCanvas::Enable()
 	{
 		glEnable(GL_DEPTH_TEST);
 		glBindFramebufferEXT(GL_FRAMEBUFFER, FFrameBuffer);
 		glPushAttrib(GL_VIEWPORT_BIT | GL_ENABLE_BIT);
 		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		if (FCanvasType==FrameCanvasContent::GBUFFER || FCanvasType==FrameCanvasContent::DEFFERED)
		{
			GLenum buffers[] = { GL_COLOR_ATTACHMENT0_EXT, GL_COLOR_ATTACHMENT1_EXT, 
                          GL_COLOR_ATTACHMENT2_EXT ,GL_COLOR_ATTACHMENT3_EXT };
    		glDrawBuffers(4, buffers);
		}
 	}

 	void TFrameCanvas::EnableSecond()
 	{
 		glEnable(GL_DEPTH_TEST);
 		glBindFramebufferEXT(GL_FRAMEBUFFER, FSecondFrameBuffer);
 		glPushAttrib(GL_VIEWPORT_BIT | GL_ENABLE_BIT);
 		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		GLenum buffers[] = { GL_COLOR_ATTACHMENT0_EXT};
		glDrawBuffers(1, buffers);
 	}

 	void TFrameCanvas::Disable()
 	{
 		glPopAttrib();
 		glBindFramebufferEXT(GL_FRAMEBUFFER, 0);
 		glClearColor (0.0, 0.0, 0.0, 0.0);
		glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 
 		glDisable(GL_DEPTH_TEST);
 	}

 	void TFrameCanvas::Draw(const std::list<TLight*>& parLights)
 	{
		if(FCanvasType==FrameCanvasContent::STANDARD)
		{
 			ShaderManager::Instance().BindTex(FAlbedoBuffer,0);
 			ShaderManager::Instance().BindTex(FDepthBuffer,1);
	 		ShaderManager::Instance().EnableShader(FShader);
		  	glBindVertexArray (FVertexArrayID);
		  	glDrawArrays(GL_TRIANGLE_STRIP, 0,4);
		  	glBindVertexArray (0);
	 		ShaderManager::Instance().DisableShader();
 			glFlush ();

		}
		else if (FCanvasType==FrameCanvasContent::GBUFFER)
		{
			ShaderManager::Instance().BindTex(FAlbedoBuffer,0);
 			ShaderManager::Instance().BindTex(FNormalBuffer,1);
 			ShaderManager::Instance().BindTex(FSpecularBuffer,2);
 			ShaderManager::Instance().BindTex(FPosBuffer,3);
 			ShaderManager::Instance().BindTex(FDepthBuffer,4);
 			int counter = FTextureCounter-FTextures.size()-1;
 			foreach_macro(tex, FTextures)
 			{
 				ShaderManager::Instance().BindTex((*tex)->FID,counter);
 				counter++;
 			}
	 		ShaderManager::Instance().EnableShader(FShader);
		  	glBindVertexArray (FVertexArrayID);
		  	glDrawArrays(GL_TRIANGLE_STRIP, 0,4);
		  	glBindVertexArray (0);
	 		ShaderManager::Instance().DisableShader();
 			glFlush ();
		}
		else if (FCanvasType==FrameCanvasContent::DEFFERED)
		{
			EnableSecond();
			glEnable (GL_BLEND); // --- could reject background frags!
			glBlendEquation (GL_FUNC_ADD);
			glBlendFunc (GL_ONE, GL_ONE); // addition each time

			glDisable (GL_DEPTH_TEST);
			glDepthMask (GL_FALSE);

			ShaderManager::Instance().BindTex(FAlbedoBuffer,0);
 			ShaderManager::Instance().BindTex(FNormalBuffer,1);
 			ShaderManager::Instance().BindTex(FSpecularBuffer,2);
 			ShaderManager::Instance().BindTex(FPosBuffer,3);
 			ShaderManager::Instance().BindTex(FDepthBuffer,4);
 			foreach_macro(light,parLights )
			{

				(*light)->Bind();
				(*light)->InjectData();
			  	glBindVertexArray (FVertexArrayID);
			  	glDrawArrays(GL_TRIANGLE_STRIP, 0,4);
			  	glBindVertexArray (0);	
				(*light)->Unbind();
			}
			glEnable (GL_DEPTH_TEST);
			glDepthMask (GL_TRUE);
			glDisable (GL_BLEND);
			Disable();

 			ShaderManager::Instance().BindTex(FFinalBuffer,0);
 			ShaderManager::Instance().BindTex(FAlbedoBuffer,1);
 			ShaderManager::Instance().BindTex(FDepthBuffer,2);
	 		ShaderManager::Instance().EnableShader(FShader);
		  	glBindVertexArray (FVertexArrayID);
		  	glDrawArrays(GL_TRIANGLE_STRIP, 0,4);
		  	glBindVertexArray (0);
	 		ShaderManager::Instance().DisableShader();
 			glFlush ();
		}
 	}

	void TFrameCanvas::AttachTexture(TTexture* _texture, const std::string& _uniformVarName)
	{
		RENDER_INFO("Attaching texture "<<_texture->FFileName<<" to frame canvas");
		FTextures.push_back(_texture);
	 	FTextureCounter++;
 		ShaderManager::Instance().EnableShader(FShader);
 		ShaderManager::Instance().InjectTex(FShader, _texture->FID, _uniformVarName, FTextureCounter);
 		ShaderManager::Instance().DisableShader();
	}
 }
