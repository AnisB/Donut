#ifndef VULKAN_BACKEND_H
#define VULKAN_BACKEND_H

// Library includes
#include "gpu_backend.h"

namespace Donut
{
	namespace VK
	{
		// Builds and returns a default graphics setting for an opengl environement
		TGraphicsSettings default_settings();
		bool init_render_system();
		RenderWindow create_render_window(const TGraphicsSettings& graphic_settings);
	}
}

#endif // VULKAN_BACKEND_H