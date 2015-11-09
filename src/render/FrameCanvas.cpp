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
 #include "graphics/common.h"
 #include "graphics/settings.h"
 #include "graphics/glfactory.h"
 #include "graphics/factory.h"

 #include <base/common.h>
 #include <multiThread/defines.h>


namespace Donut
{
	#define CANVAS_VERTEX_SHADER "shaders/canvas/vertex.glsl"
	#define CANVAS_FRAGMENT_SHADER "shaders/canvas/fragment.glsl"

 	TFrameCanvas::TFrameCanvas()
 	: FFrameBuffer(0)
 	, FMaterial()
 	, FCanvasType(FrameCanvasContent::STANDARD)
 	, FTextureCounter(0)
 	{
 		FMaterial.shader = TShader(CANVAS_VERTEX_SHADER, CANVAS_FRAGMENT_SHADER);
 	}

 	TFrameCanvas::~TFrameCanvas()
 	{
 	}

	void TFrameCanvas::Init()
 	{
 		ShaderManager::Instance().CreateShader(FMaterial.shader);
		m_fsq = CreateFullScreenQuad(FMaterial.shader);

		// Generation du buffer
		FFrameBuffer = CreateFrameBuffer();
		BindFrameBuffer(FFrameBuffer);
		GRAPHICS_DEBUG("Frame buffer init "<<FFrameBuffer);
		if(FCanvasType==FrameCanvasContent::STANDARD)
		{
			TTextureInfo& albedo = m_buffers[0];
			albedo.name = "albedo";
			albedo.type = TTextureNature::COLOR;
			albedo.offset = 0;
			CreateTexture(albedo, DEFAULT_WIDTH, DEFAULT_LENGHT);
	 		BindToFrameBuffer(albedo);

			TTextureInfo& depth = m_buffers[4];
			depth.name = "depth";
			depth.type = TTextureNature::DEPTH;
			depth.offset = 0;
			CreateTexture(depth, DEFAULT_WIDTH, DEFAULT_LENGHT);
	 		BindToFrameBuffer(depth);
 			CheckFrameBuffer();
	 		UnBindFrameBuffer();
			GRAPHICS_DEBUG("Frame canvas created");
			
	 		ShaderManager::Instance().EnableShader(FMaterial.shader);
	 		ShaderManager::Instance().Inject<int>(FMaterial.shader, DEFAULT_WIDTH, "width");
	 		ShaderManager::Instance().Inject<int>(FMaterial.shader, DEFAULT_LENGHT, "lenght");

	 		ShaderManager::Instance().InjectTex(FMaterial.shader, albedo.texID, "albedo", 0 );
	 		ShaderManager::Instance().InjectTex(FMaterial.shader, depth.texID, "depth", 1 );
	 		FTextureCounter = 2;
	 		ShaderManager::Instance().DisableShader();
		}
		else if (FCanvasType==FrameCanvasContent::DEFFERED)
		{
			// The abledo buffer
			TTextureInfo& albedo = m_buffers[0];
			albedo.name = "albedo";
			albedo.type = TTextureNature::COLOR;
			albedo.offset = 0;
			CreateTexture(albedo, DEFAULT_WIDTH, DEFAULT_LENGHT);
	 		BindToFrameBuffer(albedo);

	 		// The normal buffer
			TTextureInfo& normal = m_buffers[1];
			normal.name = "normal";
			normal.type = TTextureNature::COLOR;
			normal.offset = 1;
			CreateTexture(normal, DEFAULT_WIDTH, DEFAULT_LENGHT);
	 		BindToFrameBuffer(normal);

	 		// The specular buffer
			TTextureInfo& specular = m_buffers[2];
			specular.name = "specular";
			specular.type = TTextureNature::COLOR;
			specular.offset = 2;
			CreateTexture(specular, DEFAULT_WIDTH, DEFAULT_LENGHT);
	 		BindToFrameBuffer(specular);

	 		// Position Buffer
			TTextureInfo& position = m_buffers[3];
			position.name = "position";
			position.type = TTextureNature::COLOR;
			position.offset = 3;
			CreateTexture(position, DEFAULT_WIDTH, DEFAULT_LENGHT);
	 		BindToFrameBuffer(position);

	 		// Depth buffer
			TTextureInfo& depth = m_buffers[4];
			depth.name = "depth";
			depth.type = TTextureNature::DEPTH;
			depth.offset = 0;
			CreateTexture(depth, DEFAULT_WIDTH, DEFAULT_LENGHT);
	 		BindToFrameBuffer(depth);

	 		FTextureCounter = 4;

	 		if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
	 		{
	 			GRAPHICS_ERROR("There is a problem with your gbuffer frame buffer dude "<<glGetError());
	 		}

	 		UnBindFrameBuffer();
			GRAPHICS_DEBUG("Frame gbuffer canvas created");
		}

 	}

	void TFrameCanvas::SetShader(const TShader& _shader)
	{
		FMaterial.shader = _shader;

	}


	void TFrameCanvas::InjectData(const TShader& parShader)
	{
		if(FCanvasType==FrameCanvasContent::DEFFERED)
		{
			TTextureInfo& albedo = m_buffers[0];
			TTextureInfo& normal = m_buffers[1];
			TTextureInfo& specular = m_buffers[2];
			TTextureInfo& position = m_buffers[3];
			TTextureInfo& depth = m_buffers[4];

	 		ShaderManager::Instance().EnableShader(parShader);
	 		ShaderManager::Instance().Inject<int>(parShader, DEFAULT_WIDTH, "width");
	 		ShaderManager::Instance().Inject<int>(parShader, DEFAULT_LENGHT, "lenght");

	 		ShaderManager::Instance().InjectTex(parShader, albedo.texID, "albedo", 0 );
	 		ShaderManager::Instance().InjectTex(parShader, normal.texID, "normal", 1 );
	 		ShaderManager::Instance().InjectTex(parShader, specular.texID, "specular", 2 );
	 		ShaderManager::Instance().InjectTex(parShader, position.texID, "position", 3 );
	 		ShaderManager::Instance().InjectTex(parShader, depth.texID, "depth", 4 );
	 		ShaderManager::Instance().DisableShader();		
		}

	}	

 	void TFrameCanvas::Enable()
 	{
 		glEnable(GL_DEPTH_TEST);
 		glBindFramebufferEXT(GL_FRAMEBUFFER, FFrameBuffer);
 		glPushAttrib(GL_VIEWPORT_BIT | GL_ENABLE_BIT);
 		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		if (FCanvasType==FrameCanvasContent::DEFFERED)
		{
			GLenum buffers[] = { GL_COLOR_ATTACHMENT0_EXT, GL_COLOR_ATTACHMENT1_EXT, 
                          GL_COLOR_ATTACHMENT2_EXT ,GL_COLOR_ATTACHMENT3_EXT };
    		glDrawBuffers(4, buffers);
		}
 	}
 	void TFrameCanvas::Disable()
 	{
 		glPopAttrib();
 		glBindFramebufferEXT(GL_FRAMEBUFFER, 0);
 		glClearColor (0.0, 0.0, 0.0, 0.0);
		glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 
 		glDisable(GL_DEPTH_TEST);
 	}

 	void TFrameCanvas::Draw(const std::vector<TLight*>& parLights)
 	{
		if(FCanvasType==FrameCanvasContent::STANDARD)
		{
			TTextureInfo& albedo = m_buffers[0];
			TTextureInfo& depth = m_buffers[4];
 			ShaderManager::Instance().BindTex(albedo.texID,0);
 			ShaderManager::Instance().BindTex(depth.texID,1);
	 		ShaderManager::Instance().EnableShader(FMaterial.shader);
		  	m_fsq->Draw(false);
	 		ShaderManager::Instance().DisableShader();
 			glFlush ();

		}
		else if (FCanvasType==FrameCanvasContent::DEFFERED)
		{
			glEnable (GL_BLEND); // --- could reject background frags!
			glBlendEquation (GL_FUNC_ADD);
			glBlendFunc (GL_ONE, GL_ONE); // addition each time

			glDisable (GL_DEPTH_TEST);
			glDepthMask (GL_FALSE);

			TTextureInfo& albedo = m_buffers[0];
			TTextureInfo& normal = m_buffers[1];
			TTextureInfo& specular = m_buffers[2];
			TTextureInfo& position = m_buffers[3];
			TTextureInfo& depth = m_buffers[4];

			ShaderManager::Instance().BindTex(albedo.texID,0);
 			ShaderManager::Instance().BindTex(normal.texID,1);
 			ShaderManager::Instance().BindTex(specular.texID,2);
 			ShaderManager::Instance().BindTex(position.texID,3);
 			ShaderManager::Instance().BindTex(depth.texID,4);
 			foreach_macro(light,parLights )
			{

				(*light)->Bind();
				(*light)->InjectData();
			  	m_fsq->Draw(false);
				(*light)->Unbind();
			}
			glEnable (GL_DEPTH_TEST);
			glDepthMask (GL_TRUE);
			glDisable (GL_BLEND);
 			glFlush ();
		}
 	}

	void TFrameCanvas::AttachTexture(TTexture* _texture, const std::string& _uniformVarName)
	{
		GRAPHICS_INFO("Attaching texture "<<_texture->FFileName<<" to frame canvas");
		FTextures.push_back(_texture);
	 	FTextureCounter++;
 		ShaderManager::Instance().EnableShader(FMaterial.shader);
 		ShaderManager::Instance().InjectTex(FMaterial.shader, _texture->FID, _uniformVarName, FTextureCounter);
 		ShaderManager::Instance().DisableShader();
	}
 }
