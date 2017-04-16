// Donut includes
#include <graphics/vulkan_backend.h>


int main()
{
	Donut::TGraphicsSettings newContext = Donut::VK::default_settings();
	newContext.window_name = "testVulkan";
	Donut::VK::init_render_system();
	Donut::VK::create_render_window(newContext);
	return 0;
}