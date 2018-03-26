// Bento include
#include <bento_base/security.h>

// Engine includes
#include "render/renderer.h"
#include "Input/helper.h"
#include "graphics/glfactory.h"

// External includes 
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
 			assert(FWindow != NULL);
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
 		assert(FWindow != NULL);
 		glfwHideWindow(FWindow);
 	}	

 	void TRenderer::ShowRenderWindow()
 	{
 		GRAPHICS_DEBUG("Showing window.");	
		assert(FWindow != NULL);
 		glfwShowWindow(FWindow);
 	}	

 	bool TRenderer::Init()
 	{
 		bool isOk = true;
		// Init the render thread context
		glfwMakeContextCurrent(FWindow);
 		// initing the inputs
 		InputInit();

 		SetClearColor(bento::v4_ZERO); 
 			
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
