
// External includes
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

// Library includes
#include "gl_backend.h"
#include "common.h"
#include "containers/vector.h"

namespace Donut
{
	namespace VK
	{
		struct VKRenderEnvironment
		{
			GLFWwindow* window;
			VkInstance instance;
		};

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

		void shutdown_render_system()
		{
			glfwTerminate();
		}

		bool first_compatible_device(VkPhysicalDevice* device_array, uint64_t num_devices) 
		{
			for (uint64_t device_idx = 0; device_idx < num_devices; ++device_idx)
			{
				VkPhysicalDevice& current_device = device_array[device_idx];

				VkPhysicalDeviceProperties deviceProperties;
				VkPhysicalDeviceFeatures deviceFeatures;

				vkGetPhysicalDeviceProperties(current_device, &deviceProperties);
				vkGetPhysicalDeviceFeatures(current_device, &deviceFeatures);

				if (deviceFeatures.geometryShader && deviceFeatures.tessellationShader)
				{
					return device_idx;
				}
			}

			return -1;
		}

		RenderEnvironment create_render_environment(const TGraphicsSettings& graphic_settings)
		{
			glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);

			VKRenderEnvironment* vk_re = new VKRenderEnvironment();
			vk_re->window = glfwCreateWindow(graphic_settings.width, graphic_settings.lenght, graphic_settings.window_name.c_str(), NULL, NULL);

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
			create_info.ppEnabledExtensionNames = glfwExtensions;
			create_info.enabledLayerCount = 0;

			if (vkCreateInstance(&create_info, nullptr, &vk_re->instance) != VK_SUCCESS)
			{
				ASSERT_FAIL("Failed to create a vulkan instance");
				return 0;
			}

			// Fetch the number of devices available
			uint32_t deviceCount = 0;
			vkEnumeratePhysicalDevices(vk_re->instance, &deviceCount, nullptr);
			if (deviceCount == 0)
			{
				ASSERT_FAIL("No vulkan compatible devices");
				return 0;
			}

			TVector<VkPhysicalDevice> devices(*CommonAllocator(), deviceCount);
			vkEnumeratePhysicalDevices(vk_re->instance, &deviceCount, devices.begin());

			// Evaluate the device 
			uint64_t best_device = first_compatible_device(devices.begin(), deviceCount);

			uint32_t queueFamilyCount = 0;
			vkGetPhysicalDeviceQueueFamilyProperties(devices[best_device], &queueFamilyCount, nullptr);

			TVector<VkQueueFamilyProperties> queueFamilies(*CommonAllocator(), queueFamilyCount);
			vkGetPhysicalDeviceQueueFamilyProperties(devices[best_device], &queueFamilyCount, queueFamilies.begin());

			return (RenderEnvironment)vk_re;
		}

		void destroy_render_environment(RenderEnvironment render_environment)
		{

			VKRenderEnvironment* vk_re = (VKRenderEnvironment*)render_environment;
			vkDestroyInstance(vk_re->instance, nullptr);
			glfwDestroyWindow(vk_re->window);
		}

		RenderWindow render_window(RenderEnvironment render_environement)
		{
			VKRenderEnvironment* vk_re = (VKRenderEnvironment*)render_environement;
			return (RenderWindow)vk_re->window;
		}
	}
}