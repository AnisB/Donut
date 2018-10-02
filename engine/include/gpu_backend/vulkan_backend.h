#pragma once

#ifdef VULKAN_SUPPORTED
// Library includes
#include "gpu_backend.h"

namespace donut
{
	namespace VK
	{
		// Builds and returns a default graphics setting for an opengl environement
		TGraphicSettings default_settings();

		// API functions
		bool init_render_system();
		void shutdown_render_system();
		RenderEnvironment create_render_environment(const TGraphicSettings& graphic_settings);
		void destroy_render_environment(RenderEnvironment render_environment);
		void collect_inputs(RenderEnvironment render_environement);
		RenderWindow render_window(RenderEnvironment render_environement);
	}
}
#endif // VULKAN_BACKEND_H