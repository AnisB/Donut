// Bento includes
#include <bento_base/security.h>

// Library includes
#include "gpu_backend/gpu_backend.h"
#include "gpu_backend/gl_backend.h"
#include "gpu_backend/vulkan_backend.h"

namespace donut
{
	// Variable that holds the gpu backend
	GPUBackendAPI gpuBackendAPI[RenderingBackEnd::COUNT] = { nullptr };

	void initialize_gpu_backend(RenderingBackEnd::Type backend_type)
	{
		// Grab the target api to 
		GPUBackendAPI& currentGPUAPI = gpuBackendAPI[backend_type];
		switch (backend_type)
		{
			case RenderingBackEnd::OPENGL:
			{
				// Render system API
				currentGPUAPI.render_system_api.init_render_system = gl::render_system::init_render_system;
				currentGPUAPI.render_system_api.shutdown_render_system = gl::render_system::shutdown_render_system;
				currentGPUAPI.render_system_api.create_render_environment = gl::render_system::create_render_environment;
				currentGPUAPI.render_system_api.destroy_render_environment = gl::render_system::destroy_render_environment;
				currentGPUAPI.render_system_api.render_window = gl::render_system::render_window;
				currentGPUAPI.render_system_api.collect_inputs = gl::render_system::collect_inputs; 
				currentGPUAPI.render_system_api.get_time = gl::render_system::get_time;

				// Window API
				currentGPUAPI.window_api.hide = gl::window::hide;
				currentGPUAPI.window_api.is_active = gl::window::is_active;
				currentGPUAPI.window_api.show = gl::window::show;
				currentGPUAPI.window_api.swap = gl::window::swap;

				// Framebuffer API
				currentGPUAPI.frame_buffer_api.create = gl::framebuffer::create;
				currentGPUAPI.frame_buffer_api.destroy = gl::framebuffer::destroy;
				currentGPUAPI.frame_buffer_api.check = gl::framebuffer::check;
				currentGPUAPI.frame_buffer_api.bind = gl::framebuffer::bind;
				currentGPUAPI.frame_buffer_api.unbind = gl::framebuffer::unbind;
				currentGPUAPI.frame_buffer_api.bind_texture = gl::framebuffer::bind_texture;
				currentGPUAPI.frame_buffer_api.enable_depth_test = gl::framebuffer::enable_depth_test;
				currentGPUAPI.frame_buffer_api.disable_depth_test = gl::framebuffer::disable_depth_test;
				currentGPUAPI.frame_buffer_api.clear = gl::framebuffer::clear;
				currentGPUAPI.frame_buffer_api.set_clear_color = gl::framebuffer::set_clear_color;
				currentGPUAPI.frame_buffer_api.set_num_render_targets = gl::framebuffer::set_num_render_targets;

				// Texture 2D API
				currentGPUAPI.texture2D_api.create = gl::texture2D::create;
				currentGPUAPI.texture2D_api.destroy = gl::texture2D::destroy;
				currentGPUAPI.texture2D_api.set_debug_name = gl::texture2D::set_debug_name;

				// Texture CUBE API
				currentGPUAPI.textureCUBE_api.create = gl::textureCUBE::create;
				currentGPUAPI.textureCUBE_api.destroy = gl::textureCUBE::destroy;

				// Geometry API
				currentGPUAPI.geometry_api.create_vnt = gl::geometry::create_vnt;
				currentGPUAPI.geometry_api.destroy_vnt = gl::geometry::destroy_vnt;
				currentGPUAPI.geometry_api.draw = gl::geometry::draw;
				currentGPUAPI.geometry_api.set_bbox = gl::geometry::set_bbox;
				currentGPUAPI.geometry_api.bbox = gl::geometry::bbox;

				// Render Section API
				currentGPUAPI.render_section_api.start_render_section = gl::render_section::start_render_section;
				currentGPUAPI.render_section_api.end_render_section = gl::render_section::end_render_section;

				// Shader API
				currentGPUAPI.shader_api.create_shader = gl::shader::create_shader;
				currentGPUAPI.shader_api.create_shader_from_source = gl::shader::create_shader_from_source;
				currentGPUAPI.shader_api.destroy_shader = gl::shader::destroy_shader;

				currentGPUAPI.shader_api.bind_shader = gl::shader::bind_shader;
				currentGPUAPI.shader_api.unbind_shader = gl::shader::unbind_shader;

				currentGPUAPI.shader_api.inject_int = gl::shader::inject_int;
				currentGPUAPI.shader_api.inject_float = gl::shader::inject_float;
				currentGPUAPI.shader_api.inject_vec3 = gl::shader::inject_vec3;
				currentGPUAPI.shader_api.inject_vec4 = gl::shader::inject_vec4;
				currentGPUAPI.shader_api.inject_mat3 = gl::shader::inject_mat3;
				currentGPUAPI.shader_api.inject_mat4 = gl::shader::inject_mat4;

				currentGPUAPI.shader_api.inject_array = gl::shader::inject_array;

				currentGPUAPI.shader_api.inject_texture = gl::shader::inject_texture;

				currentGPUAPI.shader_api.inject_cubemap = gl::shader::inject_cubemap;

				// Make sure the default graphics settings are set
				currentGPUAPI.default_settings = gl::default_settings();
			}
			break;
		#if defined(VULKAN_SUPPORTED)
			case RenderingBackEnd::VULKAN:
			{
				currentGPUAPI.render_system_api.init_render_system = VK::init_render_system;
				currentGPUAPI.render_system_api.shutdown_render_system = VK::shutdown_render_system;
				currentGPUAPI.render_system_api.create_render_environment = VK::create_render_environment;
				currentGPUAPI.render_system_api.destroy_render_environment = VK::destroy_render_environment;
				currentGPUAPI.render_system_api.render_window = VK::render_window;
				currentGPUAPI.render_system_api.collect_inputs = VK::collect_inputs;
			}
			break;
		#endif
			default:
				assert_fail_msg("Unsupported RenderingBackEnd");
		};
	}

	const GPUBackendAPI* gpu_api(RenderingBackEnd::Type backend_type)
	{
		return &gpuBackendAPI[backend_type];
	}
}
