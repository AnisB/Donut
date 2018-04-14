#pragma once

// Library includes
#include "graphics/pipeline.h"
#include "graphics/pass.h"
#include "graphics/drawable.h"
#include "core/node.h"
#include "gpu_backend/gpu_backend.h"

// Bento includes
#include <bento_math/types.h>

// External includes
 #include <string>
 #include <vector>
#include <atomic>

 namespace donut
 {

 	namespace TRenderingLook
 	{
 		enum Type
 		{
	 		FILL,
 			LINE
 		};
 	}
	
	class TRenderer
	{
	public:
		// Construction/Destruction
		TRenderer();
		~TRenderer();

		// Initialisation/Destruction and context settings
		bool CreateRenderWindow(const TGraphicSettings& parContext);
		void DestroyRenderWindow();

		// Hiding and showing back the renderwindow
		void HideRenderWindow();
		void ShowRenderWindow();

		// Setting the pipeline
		void SetPipeline(TPipeline * _renderingPipeline) {m_pipeline = _renderingPipeline;}

		// Drawing the pipline
		bool Init();
		void Draw();
		void collect_inputs();

		// Rendering activation and disable
		bool IsRendering();
		void SetRendering(bool parVal);

 		// DEBUG
 		void SetLook(const TRenderingLook::Type parLook);

	protected:

		// Window Infos
		bool FInitDone;
		RenderWindow FWindow;
		RenderEnvironment _render_environement;

		bool FIsFullScreen;
		bento::IVector2 FWindowSize;
		GPUBackendAPI m_gpuBackendApi;

		// Is Rendering member
		std::atomic_bool _is_running;

		TPipeline* m_pipeline;
	};
	// END CLASS DECLARATION

	void *CreateRenderingThread(void* parGraphicRenderer);
 }