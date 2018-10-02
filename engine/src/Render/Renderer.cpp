// Bento include
#include <bento_base/security.h>

// Engine includes
#include "render/renderer.h"
#include "Input/helper.h"
#include "gpu_backend/gl_factory.h"

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

 	bool TRenderer::CreateRenderWindow(const TGraphicSettings& parContext, const GPUBackendAPI* gpuBackend)
 	{
 		if(!FInitDone)
 		{
			m_gpuBackendApi = gpuBackend;

			// Init the render backend
			m_gpuBackendApi->render_system_api.init_render_system();
			// Create a window
			_render_environement = m_gpuBackendApi->render_system_api.create_render_environment(parContext);
			FWindow = m_gpuBackendApi->render_system_api.render_window(_render_environement);
			_is_running = true;
			FInitDone = true;
 		}
 		else
 		{
			ShowRenderWindow();
 		}
 		return true;
 	}
 	
 	void TRenderer::DestroyRenderWindow()
 	{
		if (FInitDone)
		{
			m_gpuBackendApi->render_system_api.destroy_render_environment((uint64_t)FWindow);
			m_gpuBackendApi->render_system_api.shutdown_render_system();
			FInitDone = false;
		}
 	}	

 	void TRenderer::HideRenderWindow()
 	{
 		assert(FWindow != NULL);
		m_gpuBackendApi->window_api.hide(FWindow);
	}

 	void TRenderer::ShowRenderWindow()
 	{
		assert(FWindow != NULL);
		m_gpuBackendApi->window_api.show(FWindow);
	}

 	bool TRenderer::Init()
 	{
 		bool isOk = true;

		m_gpuBackendApi->frame_buffer_api.set_clear_color(0, bento::v4_ZERO);
 			
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
			//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		}
		else if(parLook == TRenderingLook::FILL)
		{
			//glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		}
	}

 	void TRenderer::Draw()
 	{ 	 
		// We clear the global buffer
		m_gpuBackendApi->frame_buffer_api.clear(0);

		uint32_t nbPasses = (uint32_t)m_pipeline->passes.size();
        for(uint32_t pass = 0; pass < nbPasses; ++pass)
        {
        	TPass * currentPass = m_pipeline->passes[pass];
			m_gpuBackendApi->render_section_api.start_render_section(currentPass->name());
			currentPass->Bind();
			currentPass->Draw(m_pipeline->pipelineData);
			currentPass->Unbind();
			m_gpuBackendApi->render_section_api.end_render_section();
		}
		// Swap front and back buffer
		m_gpuBackendApi->window_api.swap(FWindow);
    }

	bool TRenderer::IsRendering()
	{
		return (_is_running && m_gpuBackendApi->window_api.is_active(FWindow));

	}

	void TRenderer::collect_inputs()
	{
		m_gpuBackendApi->render_system_api.collect_inputs(_render_environement);
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
		while(realGraphicRenderer->IsRendering())
		{
			realGraphicRenderer->Draw();
		}
		return 0;
	}
}
