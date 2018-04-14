#pragma once

// Library includes
#include "gpu_backend.h"

namespace donut
{
	namespace gl
	{
		namespace GLData
		{
			enum Type
			{
				ERROR_CALLBACK = 0,
				MAJOR_VERSION = 1,
				MINOR_VERSION = 2
 			};
		}

		// Builds and returns a default graphics setting for an opengl environement
		TGraphicSettings default_settings();

		// API functions
		bool init_render_system();
		void shutdown_render_system();
		RenderEnvironment create_render_environment(const TGraphicSettings& graphic_settings);
		void destroy_render_environment(RenderEnvironment render_environment);
		RenderWindow render_window(RenderEnvironment render_environement);
		void collect_inputs(RenderEnvironment render_environement);
		float get_time();
	}
}