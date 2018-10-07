#ifdef VULKAN_SUPPORTED

// External includes
#if defined(WIN32)
	#define VK_USE_PLATFORM_WIN32_KHR
	#include <vulkan/vulkan.h>
	#define GLFW_INCLUDE_VULKAN
	#define GLFW_EXPOSE_NATIVE_WIN32
	#define GLFW_EXPOSE_NATIVE_WGL
	#include <windows.h>
	#include <GLFW/glfw3.h>
	#include <GLFW/glfw3native.h>
#endif

// Bento includes
#include <bento_base/security.h>
#include <bento_memory/common.h>
#include <bento_collection/vector.h>

// Library includes
#include "gpu_backend/gpu_backend.h"

namespace donut
{
	namespace VK
	{
		struct TQueueIndexes
		{
			TQueueIndexes()
			: graphics_queue(-1)
			, present_queue(-1)
			{

			}
			uint64_t graphics_queue;
			uint64_t present_queue;
		};

		struct VKRenderEnvironment
		{
			GLFWwindow* window;
			VkInstance instance;
			VkPhysicalDevice physical_device;
			VkDevice logical_device;
			VkSurfaceKHR surface;
			TQueueIndexes queue_indexes;
		};

		// Builds and returns a default graphics setting for an opengl environement
		TGraphicSettings default_settings()
		{
			TGraphicSettings settings;
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

		uint64_t first_compatible_device(VkPhysicalDevice* device_array, uint64_t num_devices)
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

		void find_graphics_queue(VkQueueFamilyProperties* queue_array, uint64_t num_queues, TQueueIndexes& output_queues)
		{
			// Check for the queues
			TQueueIndexes queue_data;
			for (uint64_t queue_idx = 0; queue_idx < num_queues; ++queue_idx)
			{
				VkQueueFamilyProperties& current_queue = queue_array[queue_idx];
				if (current_queue.queueCount > 0 && current_queue.queueFlags & VK_QUEUE_GRAPHICS_BIT)
				{
					output_queues.graphics_queue = queue_idx;
					return;
				}
			}
		}

		void find_present_queue(VKRenderEnvironment* vk_re, uint32_t num_queues)
		{
			// Check for the queues
			for (uint32_t queue_idx = 0; queue_idx < num_queues; ++queue_idx)
			{
				VkBool32 present_support;
				vkGetPhysicalDeviceSurfaceSupportKHR(vk_re->physical_device, queue_idx, vk_re->surface, &present_support);
				if (present_support)
				{
					vk_re->queue_indexes.present_queue = queue_idx;
					return;
				}
			}
		}

		VkQueue retrieve_queue_by_index(VKRenderEnvironment* render_environement, uint32_t queue_index)
		{
			assert(render_environement);
			VkQueue graphicsQueue;
			vkGetDeviceQueue(render_environement->logical_device, queue_index, 0, &graphicsQueue);
			return graphicsQueue;
		}
		
		RenderEnvironment create_render_environment(const TGraphicSettings& graphic_settings)
		{
			bento::IAllocator* allocator = bento::common_allocator();
			assert(allocator != nullptr);

			glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);

			VKRenderEnvironment* vk_re = bento::make_new<VKRenderEnvironment>(*allocator);
			vk_re->window = glfwCreateWindow(graphic_settings.width, graphic_settings.lenght, graphic_settings.window_name.c_str(), NULL, NULL);

			uint32_t extension_count = 0;
			vkEnumerateInstanceExtensionProperties(nullptr, &extension_count, nullptr);

			VkApplicationInfo app_info = {};
			app_info.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
			app_info.pApplicationName = graphic_settings.window_name.c_str();
			app_info.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
			app_info.pEngineName = "donut";
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
				assert_fail_msg("Failed to create a vulkan instance");
				return 0;
			}

			// Fetch the number of devices available
			uint32_t deviceCount = 0;
			vkEnumeratePhysicalDevices(vk_re->instance, &deviceCount, nullptr);
			if (deviceCount == 0)
			{
				assert_fail_msg("No vulkan compatible devices");
				return 0;
			}

			bento::Vector<VkPhysicalDevice> devices(*bento::common_allocator(), deviceCount);
			vkEnumeratePhysicalDevices(vk_re->instance, &deviceCount, devices.begin());

			// Evaluate the device 
			uint64_t best_device = first_compatible_device(devices.begin(), deviceCount);
			assert_msg(best_device != -1, "No compatible vulkan device");
			// Keep track of the phyisical device
			vk_re->physical_device = devices[best_device];

			uint32_t queueFamilyCount = 0;
			vkGetPhysicalDeviceQueueFamilyProperties(vk_re->physical_device, &queueFamilyCount, nullptr);

			bento::Vector<VkQueueFamilyProperties> queueFamilies(*bento::common_allocator(), queueFamilyCount);
			vkGetPhysicalDeviceQueueFamilyProperties(vk_re->physical_device, &queueFamilyCount, queueFamilies.begin());
			
			// Check for the queues
			find_graphics_queue(queueFamilies.begin(), queueFamilyCount, vk_re->queue_indexes);
			assert_msg(vk_re->queue_indexes.graphics_queue != -1, "No valid graphics queue found");

			// Queue creation descriptor
			VkDeviceQueueCreateInfo queue_create_info = {};
			queue_create_info.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
			queue_create_info.queueFamilyIndex = vk_re->queue_indexes.graphics_queue;
			queue_create_info.queueCount = 1;
			float queue_priority = 1.0f;
			queue_create_info.pQueuePriorities = &queue_priority;

			VkDeviceCreateInfo device_create_info = {};
			device_create_info.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
			device_create_info.pQueueCreateInfos = &queue_create_info;
			device_create_info.queueCreateInfoCount = 1;
			VkPhysicalDeviceFeatures deviceFeatures = {};
			device_create_info.pEnabledFeatures = &deviceFeatures;
			device_create_info.enabledExtensionCount = 0;
			device_create_info.enabledLayerCount = 0;

			if (vkCreateDevice(devices[best_device], &device_create_info, nullptr, &vk_re->logical_device) != VK_SUCCESS)
			{
				assert_fail_msg("Logical device creation failed");
				return 0;
			}

			// Create the surface
			if (glfwCreateWindowSurface(vk_re->instance, vk_re->window, nullptr, &(vk_re->surface)) != VK_SUCCESS)
				assert_fail_msg("Surface creation failed");

			// Queck for the present support
			find_present_queue(vk_re, queueFamilyCount);

			return (RenderEnvironment)vk_re;
		}

		void destroy_render_environment(RenderEnvironment render_environment)
		{
			VKRenderEnvironment* vk_re = (VKRenderEnvironment*)render_environment;
			vkDestroySurfaceKHR(vk_re->instance, vk_re->surface, nullptr);
			vkDestroyDevice(vk_re->logical_device, nullptr);
			vkDestroyInstance(vk_re->instance, nullptr);
			glfwDestroyWindow(vk_re->window);
			bento::make_delete<VKRenderEnvironment>(*bento::common_allocator(), vk_re);
		}

		RenderWindow render_window(RenderEnvironment render_environement)
		{
			VKRenderEnvironment* vk_re = (VKRenderEnvironment*)render_environement;
			return (RenderWindow)vk_re->window;
		}

		void collect_inputs(RenderEnvironment render_environement)
		{
			glfwPollEvents();
		}
	}
}

#endif // VULKAN_SUPPORTED