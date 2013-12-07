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
 #include "Base/Common.h"
 #include "MultiThread/Defines.h"


namespace Donut
{
 	TFrameCanvas::TFrameCanvas()
 	: TDrawableObject()
 	, FFrameBuffer(0)
 	, FRenderTexture(0)
 	, FDepthBuffer(0)
 	, FShader(0,BASIC_VERTEX_SHADER,BASIC_FRAGMENT_SHADER)
 	{

 	}

 	TFrameCanvas::~TFrameCanvas()
 	{
 	}
 	
	void TFrameCanvas::Init()
 	{
 		glEnable(GL_TEXTURE_2D);

		#ifdef LINUX
		glGenFramebuffers(1, &FFrameBuffer);
 		glBindFramebuffer(GL_FRAMEBUFFER, FFrameBuffer);
 		#endif
 		#ifdef MACOSX
		glGenFramebuffersEXT(1, &FFrameBuffer);
 		glBindFramebufferEXT(GL_FRAMEBUFFER, FFrameBuffer);
 		#endif
		RENDER_DEBUG("Frame buffer init "<<FFrameBuffer);

 		glGenTextures(1, &FRenderTexture);
 		glBindTexture(GL_TEXTURE_2D, FRenderTexture);
 		glTexImage2D(GL_TEXTURE_2D, 0,GL_RGBA, DEFAULTW, DEFAULTL, 0,GL_RGBA, GL_UNSIGNED_BYTE, 0);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
 		glBindTexture(GL_TEXTURE_2D, 0);

		#ifdef LINUX
 		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0,  GL_TEXTURE_2D, FRenderTexture,0);
 		#endif

 		#ifdef MACOSX
 		glFramebufferTextureEXT(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0_EXT, FRenderTexture,0);
 		#endif

 		glGenTextures(1, &FDepthBuffer);
 		glBindTexture(GL_TEXTURE_2D, FDepthBuffer);
 		glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT24, DEFAULTW, DEFAULTL, 0, GL_DEPTH_COMPONENT, GL_UNSIGNED_BYTE, NULL);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
 		glBindTexture(GL_TEXTURE_2D, 0);
 		#ifdef LINUX
 		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, FDepthBuffer,0);
 		#endif
 		
 		#ifdef MACOSX
 		glFramebufferTextureEXT(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, FDepthBuffer, 0);
 		#endif

 		if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
 		{
 			RENDER_DEBUG("There is a problem with your frame buffer dude "<<glGetError());
 		}
 		#ifdef LINUX
 		glBindFramebuffer(1, 0);
 		#endif
 		
 		#ifdef MACOSX
 		glBindFramebufferEXT(1, 0);
 		#endif
 		FShader = ShaderManager::Instance().CreateShader(FShader.FVertexShader,FShader.FFragmentShader);
		RENDER_DEBUG("Frame canvas created");
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
 		glEnable(GL_TEXTURE_2D);
 		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LEQUAL); 
 		glBindFramebufferEXT(GL_FRAMEBUFFER, FFrameBuffer);
 		glPushAttrib(GL_VIEWPORT_BIT | GL_ENABLE_BIT);
 		glViewport(0,0,DEFAULTW, DEFAULTL);
 		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
 		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
 	}

 	void TFrameCanvas::Disable()
 	{
 		glPopAttrib();
 		glBindFramebufferEXT(GL_FRAMEBUFFER, 0);
 		glClearColor (0.0f, 0.0f, 0.0f, 0.5f);
		glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);   
 	}

 	void TFrameCanvas::Draw()
 	{
 		ShaderManager::Instance().EnableShader(FShader);

		
 		GLint depth = glGetUniformLocation(FShader.FProgramID, "depth");
       	glActiveTexture(GL_TEXTURE1);
 		glBindTexture(GL_TEXTURE_2D, FDepthBuffer);
		glUniform1i(depth, 1);		

 		GLint tex0 = glGetUniformLocation(FShader.FProgramID, "canvas");
       	glActiveTexture(GL_TEXTURE0);
 		glBindTexture(GL_TEXTURE_2D, FRenderTexture);
		glUniform1i(tex0, 0);

 		glBegin(GL_QUADS);
 		glVertex2f(-1, -1);  
 		glVertex2f(1 , -1);
 		glVertex2f(1, 1);
 		glVertex2f(-1, 1);
 		glEnd();
 		glBindTexture(GL_TEXTURE_2D, 0);
 		ShaderManager::Instance().DisableShader();

 		glDisable(GL_TEXTURE_2D);
 		glDisable(GL_DEPTH_TEST);
 		glFlush ();
 	}
 }
