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

#pragma once

// Library includes
#include "graphics/common.h"
#include "graphics/pipeline.h"
#include "graphics/settings.h"
#include "graphics/pass.h"
#include "graphics/drawable.h"
#include "core/node.h"
#include "graphics/gpu_backend.h"

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
		bool CreateRenderWindow(const TGraphicsSettings& parContext);
		void DestroyRenderWindow();

		// Hiding and showing back the renderwindow
		void HideRenderWindow();
		void ShowRenderWindow();

		// Setting the pipeline
		void SetPipeline(TPipeline * _renderingPipeline) {m_pipeline = _renderingPipeline;}

		// Drawing the pipline
		bool Init();
		void Draw();

		// Rendering activation and disable
		bool IsRendering();
		void SetRendering(bool parVal);

 		// DEBUG
 		void SetLook(const TRenderingLook::Type parLook);

 	private:
 		void InputInit();

	protected:

		// Window Infos
		bool FInitDone;
		GLFWwindow * FWindow;
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