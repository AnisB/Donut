#ifndef GPU_BACKEND_H
#define GPU_BACKEND_H

// Library includes
#include "settings.h"

namespace Donut
{
	// Types definition
	typedef uint64_t RenderWindow;

	struct GPUBackendAPI
	{
		bool (*init_render_system)();
		RenderWindow (*create_render_windows)(TGraphicsSettings& graphic_settings);
	};
}

#endif // GPU_BACKEND_H