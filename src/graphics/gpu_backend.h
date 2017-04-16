#ifndef GPU_BACKEND_H
#define GPU_BACKEND_H

// Library includes
#include "settings.h"

namespace Donut
{
	// Types definition
	typedef uint64_t RenderEnvironment;
	typedef uint64_t RenderWindow;

	struct GPUBackendAPI
	{
		bool (*init_render_system)();
		void (*shutdown_render_system)();
		RenderEnvironment(*create_render_environment)(TGraphicsSettings& graphic_settings);
		void (*destroy_render_environment)(RenderEnvironment render_environment);
		RenderWindow (*render_window)(RenderEnvironment _render);
	};
}

#endif // GPU_BACKEND_H