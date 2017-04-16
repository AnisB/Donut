#ifndef GL_BACKEND_H
#define GL_BACKEND_H

// Library includes
#include "gpu_backend.h"

namespace Donut
{
	namespace GL
	{
		typedef void (*ErrorCallBack)(int error, const char* description);

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
		TGraphicsSettings default_settings();

		// API functions
		bool init_render_system();
		void shutdown_render_system();
		RenderEnvironment create_render_environment(const TGraphicsSettings& graphic_settings);
		void destroy_render_environment(RenderEnvironment render_environment);
		RenderWindow render_window(RenderEnvironment render_environement);
	}
}

#endif // GL_BACKEND_H