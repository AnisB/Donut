
// External includes
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

// Library includes
#include "gl_backend.h"
#include "common.h"

namespace Donut
{
	namespace VK
	{
		// Builds and returns a default graphics setting for an opengl environement
		TGraphicsSettings default_settings()
		{
			TGraphicsSettings settings;
			settings.backend = RenderingBackEnd::VULKAN;
			settings.width = 1280;
			settings.lenght = 720;
			return settings;
		}

		bool init_render_system()
		{
			return glfwInit() && glfwVulkanSupported();
		}

		RenderWindow create_render_window(const TGraphicsSettings& graphic_settings)
		{
			glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
			GLFWwindow* window = glfwCreateWindow(graphic_settings.width, graphic_settings.lenght, graphic_settings.window_name.c_str(), NULL, NULL);

			uint32_t extension_count = 0;
			vkEnumerateInstanceExtensionProperties(nullptr, &extension_count, nullptr);

			VkApplicationInfo app_info = {};
			app_info.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
			app_info.pApplicationName = graphic_settings.window_name.c_str();
			app_info.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
			app_info.pEngineName = "Donut";
			app_info.engineVersion = VK_MAKE_VERSION(1, 0, 0);
			app_info.apiVersion = VK_API_VERSION_1_0;

			VkInstanceCreateInfo create_info = {};
			create_info.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
			create_info.pApplicationInfo = &app_info;

			unsigned int glfwExtensionCount = 0;
			const char ** glfwExtensions;
			glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

			create_info.enabledExtensionCount = glfwExtensionCount;
			create_info.enabledLayerCount = 0;

			VkInstance instance;
			if (vkCreateInstance(&create_info, nullptr, &instance) != VK_SUCCESS)
			{
				return 0;
			}


			return (uint64_t)instance;
		}
	}
}