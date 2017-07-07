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


#include "Renderer.h"

#include "Input/helper.h"
#include "graphics/glfactory.h"
 
#include <stdlib.h>
#include <stdio.h>
 
 namespace donut
 {
	// Class TRenderer
 	TRenderer::TRenderer()
 	: FWindowSize()
 	, FIsFullScreen(false)
 	, FWindow(NULL)
 	, _is_running(false)
 	, FInitDone(false)
 	{

 	}
 	TRenderer::~TRenderer()
 	{
		_is_running = false;
 	}

 	bool TRenderer::CreateRenderWindow(const TGraphicsSettings& parContext)
 	{
 		if(!FInitDone)
 		{
			// Fetch the GL rendering backend
			build_rendering_backend(RenderingBackEnd::OPENGL, m_gpuBackendApi);

			// Init the render backend
			m_gpuBackendApi.init_render_system();
			// Create a window
			FWindow = (GLFWwindow*)m_gpuBackendApi.render_window(m_gpuBackendApi.create_render_environment(parContext));
			_is_running = true;
			FInitDone = true;
 		}
 		else
 		{
 			GRAPHICS_DEBUG("This window has already been created.");
 			ASSERT(FWindow != NULL);
 			glfwShowWindow(FWindow);
 		}
 		return true;
 	}
 	
 	void TRenderer::DestroyRenderWindow()
 	{
		if (FInitDone)
		{
			GRAPHICS_DEBUG("Destroying window.");
			m_gpuBackendApi.destroy_render_environment((uint64_t)FWindow);
			m_gpuBackendApi.shutdown_render_system();
			FInitDone = false;
		}
 	}	

 	void TRenderer::HideRenderWindow()
 	{
 		GRAPHICS_DEBUG("Hiding window.");	
 		ASSERT(FWindow != NULL);
 		glfwHideWindow(FWindow);
 	}	

 	void TRenderer::ShowRenderWindow()
 	{
 		GRAPHICS_DEBUG("Showing window.");	
 		ASSERT(FWindow != NULL);
 		glfwShowWindow(FWindow);
 	}	

 	bool TRenderer::Init()
 	{
 		bool isOk = true;
		// Init the render thread context
		glfwMakeContextCurrent(FWindow);
 		// initing the inputs
 		InputInit();

 		SetClearColor(v4_ZERO); 
 			
		uint64_t nbPasses = m_pipeline->passes.size();
        for(size_t pass = 0; pass < nbPasses; ++pass)
        {
        	m_pipeline->passes[pass]->Init();
        }
        m_pipeline->BuildPipelineData();
		return isOk;
 	}
 	
	void TRenderer::SetLook(const TRenderingLook::Type parLook)
	{
		if(parLook == TRenderingLook::LINE)
		{
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		}
		else if(parLook == TRenderingLook::FILL)
		{
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		}
	}

 	void TRenderer::Draw()
 	{ 	 
		// We clear the global buffer
 		ClearBuffer();
		int nbPasses = m_pipeline->passes.size();
        for(size_t pass = 0; pass < nbPasses; ++pass)
        {
        	TPass * currentPass = m_pipeline->passes[pass];
			currentPass->Bind();
			currentPass->Draw(m_pipeline->pipelineData);
			currentPass->Unbind();
        }
		// Swap front and back buffer
	  	glfwSwapBuffers (FWindow);
    }

	void TRenderer::InputInit()
	{
		glfwSetKeyCallback(FWindow, key_callback);
		glfwSetMouseButtonCallback(FWindow, mouse_button_callback);
		glfwSetScrollCallback(FWindow, mouse_scroll_callback);
		glfwSetCursorPosCallback(FWindow, mouse_pos_callback);
	}

	bool TRenderer::IsRendering()
	{
		return (_is_running && !glfwWindowShouldClose(FWindow));

	}

	void TRenderer::SetRendering(bool parVal)
	{
		_is_running = parVal;
	}

	// END CLASS DECLARATION
	
	void *CreateRenderingThread(void* parGraphicRenderer)
	{
		TRenderer * realGraphicRenderer = (TRenderer*) parGraphicRenderer;
		realGraphicRenderer->Init();
		GRAPHICS_DEBUG("Init is done.");
		while(realGraphicRenderer->IsRendering())
		{
			realGraphicRenderer->Draw();
		}
		GRAPHICS_DEBUG("Window isn't rendering anymore");
		return 0;
	}
}
