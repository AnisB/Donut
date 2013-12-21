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
 #include "Render/Defines.h"
 #include <Render/Helper.h>
 #include "Base/Common.h"
 #include "MultiThread/Defines.h"


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
 	, FShader(0,CANVAS_VERTEX_SHADER,CANVAS_FRAGMENT_SHADER)
 	, FCanvasType(FrameCanvasContent::STANDARD)
 	{

 	}

 	TFrameCanvas::~TFrameCanvas()
 	{
 	}

	void TFrameCanvas::createShader()
	{
 		FShader = ShaderManager::Instance().CreateShader(FShader.FVertexShader,FShader.FFragmentShader);
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
	 		CreateTexture(FAlbedoBuffer, DEFAULTW, DEFAULTL, TextureNature::COLOR);
	 		BindToFrameBuffer(FAlbedoBuffer, TextureNature::COLOR, 0);

	 		CreateTexture(FDepthBuffer, DEFAULTW, DEFAULTL, TextureNature::DEPTH);
	 		BindToFrameBuffer(FDepthBuffer, TextureNature::DEPTH, 0);
 			CheckGLState("Depth");

	 		if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
	 		{
	 			RENDER_ERR("There is a problem with your standard frame buffer dude "<<glGetError());
	 		}

	 		UnBindFrameBuffer();
			RENDER_DEBUG("Frame canvas created");
			
	 		ShaderManager::Instance().EnableShader(FShader);
	 		ShaderManager::Instance().InjectInt(FShader, DEFAULTW, "width");
	 		ShaderManager::Instance().InjectInt(FShader, DEFAULTL, "lenght");

	 		ShaderManager::Instance().InjectTex(FShader, FAlbedoBuffer, "canvas", 0 );
	 		ShaderManager::Instance().InjectTex(FShader, FDepthBuffer, "depth", 1 );
	 		ShaderManager::Instance().DisableShader();
		}
		else if (FCanvasType==FrameCanvasContent::GBUFFER)
		{
	 		CreateTexture(FAlbedoBuffer, DEFAULTW, DEFAULTL, TextureNature::COLOR);
	 		BindToFrameBuffer(FAlbedoBuffer, TextureNature::COLOR, 0);

	 		CreateTexture(FNormalBuffer, DEFAULTW, DEFAULTL, TextureNature::COLOR);
	 		BindToFrameBuffer(FNormalBuffer, TextureNature::COLOR, 1);

	 		CreateTexture(FSpecularBuffer, DEFAULTW, DEFAULTL, TextureNature::COLOR);
	 		BindToFrameBuffer(FSpecularBuffer, TextureNature::COLOR, 2);

	 		CreateTexture(FDepthBuffer, DEFAULTW, DEFAULTL, TextureNature::DEPTH);
	 		BindToFrameBuffer(FDepthBuffer, TextureNature::DEPTH, 0);

	 		if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
	 		{
	 			RENDER_ERR("There is a problem with your gbuffer frame buffer dude "<<glGetError());
	 		}

	 		UnBindFrameBuffer();
			RENDER_DEBUG("Frame gbuffer canvas created");
			
	 		ShaderManager::Instance().EnableShader(FShader);
	 		ShaderManager::Instance().InjectInt(FShader, DEFAULTW, "width");
	 		ShaderManager::Instance().InjectInt(FShader, DEFAULTL, "lenght");

	 		ShaderManager::Instance().InjectTex(FShader, FAlbedoBuffer, "canvas", 0 );
	 		ShaderManager::Instance().InjectTex(FShader, FNormalBuffer, "nbuffer", 1 );
	 		ShaderManager::Instance().InjectTex(FShader, FSpecularBuffer, "specbuffer", 2 );
	 		ShaderManager::Instance().InjectTex(FShader, FDepthBuffer, "depth", 3 );

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

 	void TFrameCanvas::Enable()
 	{
 		glEnable(GL_DEPTH_TEST);
 		glBindFramebufferEXT(GL_FRAMEBUFFER, FFrameBuffer);
 		glPushAttrib(GL_VIEWPORT_BIT | GL_ENABLE_BIT);
 		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		if (FCanvasType==FrameCanvasContent::GBUFFER)
		{
			GLenum buffers[] = { GL_COLOR_ATTACHMENT0_EXT, GL_COLOR_ATTACHMENT1_EXT, 
                          GL_COLOR_ATTACHMENT2_EXT };
    		glDrawBuffers(3, buffers);
		}

 	}

 	void TFrameCanvas::Disable()
 	{
 		glPopAttrib();
 		glBindFramebufferEXT(GL_FRAMEBUFFER, 0);
 		glClearColor (1.0, 1.0, 1.0, 0.0);
		glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 
 		glDisable(GL_DEPTH_TEST);
 	}

 	void TFrameCanvas::Draw()
 	{
		if(FCanvasType==FrameCanvasContent::STANDARD)
		{
 			ShaderManager::Instance().BindTex(FAlbedoBuffer,0);
 			ShaderManager::Instance().BindTex(FDepthBuffer,1);
		}
		else if (FCanvasType==FrameCanvasContent::GBUFFER)
		{
			ShaderManager::Instance().BindTex(FAlbedoBuffer,0);
 			ShaderManager::Instance().BindTex(FNormalBuffer,1);
 			ShaderManager::Instance().BindTex(FSpecularBuffer,2);
 			ShaderManager::Instance().BindTex(FDepthBuffer,3);
		}

 		ShaderManager::Instance().EnableShader(FShader);

	  	glBindVertexArray (FVertexArrayID);
	  	glDrawArrays(GL_TRIANGLE_STRIP, 0,4);
	  	glBindVertexArray (0);

 		ShaderManager::Instance().DisableShader();

 		glFlush ();
 	}
 }
