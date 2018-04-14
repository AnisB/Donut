// Bento includes
#include <bento_base/security.h>

// Library includes
#include "gpu_backend/gpu_backend.h"
#include "gpu_backend/gl_backend.h"
#include "gpu_backend/vulkan_backend.h"

namespace donut
{
	void build_rendering_backend(RenderingBackEnd::Type backend_type, GPUBackendAPI& backend_api)
	{
		switch (backend_type)
		{
			case RenderingBackEnd::OPENGL:
			{
				backend_api.init_render_system = gl::init_render_system;
				backend_api.shutdown_render_system = gl::shutdown_render_system;
				backend_api.create_render_environment = gl::create_render_environment;
				backend_api.destroy_render_environment = gl::destroy_render_environment;
				backend_api.render_window = gl::render_window;
				backend_api.collect_inputs = gl::collect_inputs;
			}
			break;
		#if defined(VULKAN_SUPPORTED)
			case RenderingBackEnd::VULKAN:
			{
				backend_api.init_render_system = VK::init_render_system;
				backend_api.shutdown_render_system = VK::shutdown_render_system;
				backend_api.create_render_environment = VK::create_render_environment;
				backend_api.destroy_render_environment = VK::destroy_render_environment;
				backend_api.render_window = VK::render_window;
				backend_api.collect_inputs = VK::collect_inputs;
			}
			break;
		#endif
			default:
				assert_fail_msg("Unsupported RenderingBackEnd");
		};
	}
}
