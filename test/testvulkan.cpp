#ifdef VULKAN_SUPPORTED
// donut includes
#include <gpu_backend/vulkan_backend.h>

using namespace donut;

int main()
{
	TGraphicSettings newContext = VK::default_settings();
	newContext.window_name = "testVulkan";
	VK::init_render_system();
	RenderEnvironment env = VK::create_render_environment(newContext);
	VK::destroy_render_environment(env);
	VK::shutdown_render_system();
	return 0;
}
#endif // VULKAN_SUPPORTED