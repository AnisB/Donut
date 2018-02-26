// Library includes
#include "graphics/gpu_backend.h"
#include "graphics/gl_backend.h"
#include "graphics/vulkan_backend.h"
#include "base/security.h"

namespace donut
{
	void build_rendering_backend(RenderingBackEnd::Type backend_type, GPUBackendAPI& backend_api)
	{
		switch (backend_type)
		{
			case RenderingBackEnd::OPENGL:
			{
				backend_api.init_render_system = GL::init_render_system;
				backend_api.shutdown_render_system = GL::shutdown_render_system;
				backend_api.create_render_environment = GL::create_render_environment;
				backend_api.destroy_render_environment = GL::destroy_render_environment;
				backend_api.render_window = GL::render_window;
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
			}
			break;
		#endif
			default:
				ASSERT_FAIL_MSG("Unsupported RenderingBackEnd");
		};
	}
}
