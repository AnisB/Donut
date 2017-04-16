#ifndef VULKAN_BACKEND_H
#define VULKAN_BACKEND_H

#ifdef VULKAN_SUPPORTED
// Library includes
#include "gpu_backend.h"

namespace Donut
{
	namespace VK
	{
		// Builds and returns a default graphics setting for an opengl environement
		TGraphicsSettings default_settings();

		// API functions
		bool init_render_system();
		void shutdown_render_system();
		RenderEnvironment create_render_environment(const TGraphicsSettings& graphic_settings);
		void destroy_render_environment(RenderEnvironment render_environment);
		RenderWindow render_window(RenderEnvironment render_environement);
	}
}
#endif // VULKAN_SUPPORTED
#endif // VULKAN_BACKEND_H