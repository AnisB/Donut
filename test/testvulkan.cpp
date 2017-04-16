// Donut includes
#include <graphics/vulkan_backend.h>


int main()
{
	Donut::TGraphicsSettings newContext = Donut::VK::default_settings();
	newContext.window_name = "testVulkan";
	Donut::VK::init_render_system();
	Donut::RenderEnvironment env = Donut::VK::create_render_environment(newContext);
	Donut::VK::destroy_render_environment(env);
	Donut::VK::shutdown_render_system();
	return 0;
}