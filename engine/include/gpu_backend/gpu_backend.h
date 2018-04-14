#pragma once

// Library includes
#include "settings.h"

// External includes
#include <stdint.h>

namespace donut
{
	namespace RenderingBackEnd
	{
		enum Type
		{
			OPENGL = 0,
			VULKAN = 1,
			D12 = 2
		};
	}

	// Types definition
	typedef uint64_t RenderEnvironment;
	typedef uint64_t RenderWindow;
	typedef uint64_t GeometryObject;

	struct GPUBackendAPI
	{
		bool (*init_render_system)();
		void (*shutdown_render_system)();
		RenderEnvironment (*create_render_environment)(const TGraphicSettings& graphic_settings);
		void (*destroy_render_environment)(RenderEnvironment render_environment);
		RenderWindow (*render_window)(RenderEnvironment _render);
		void (*collect_inputs)(RenderEnvironment render_environement);
		float (*get_time)(RenderEnvironment render_environement);
	};

	void build_rendering_backend(RenderingBackEnd::Type backend_type, GPUBackendAPI& backend_api);
}