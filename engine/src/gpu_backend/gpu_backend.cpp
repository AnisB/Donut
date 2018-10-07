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
				// Render system API
				currentGPUAPI.render_system_api.init_render_system = vk::render_system::init_render_system;
				currentGPUAPI.render_system_api.shutdown_render_system = vk::render_system::shutdown_render_system;
				currentGPUAPI.render_system_api.create_render_environment = vk::render_system::create_render_environment;
				currentGPUAPI.render_system_api.destroy_render_environment = vk::render_system::destroy_render_environment;
				currentGPUAPI.render_system_api.render_window = vk::render_system::render_window;
				currentGPUAPI.render_system_api.collect_inputs = vk::render_system::collect_inputs;
				currentGPUAPI.render_system_api.get_time = vk::render_system::get_time;

				// Window API
				currentGPUAPI.window_api.hide = vk::window::hide;
				currentGPUAPI.window_api.is_active = vk::window::is_active;
				currentGPUAPI.window_api.show = vk::window::show;
				currentGPUAPI.window_api.swap = vk::window::swap;

				// Framebuffer API
				currentGPUAPI.frame_buffer_api.create = vk::framebuffer::create;
				currentGPUAPI.frame_buffer_api.destroy = vk::framebuffer::destroy;
				currentGPUAPI.frame_buffer_api.check = vk::framebuffer::check;
				currentGPUAPI.frame_buffer_api.bind = vk::framebuffer::bind;
				currentGPUAPI.frame_buffer_api.unbind = vk::framebuffer::unbind;
				currentGPUAPI.frame_buffer_api.bind_texture = vk::framebuffer::bind_texture;
				currentGPUAPI.frame_buffer_api.enable_depth_test = vk::framebuffer::enable_depth_test;
				currentGPUAPI.frame_buffer_api.disable_depth_test = vk::framebuffer::disable_depth_test;
				currentGPUAPI.frame_buffer_api.clear = vk::framebuffer::clear;
				currentGPUAPI.frame_buffer_api.set_clear_color = vk::framebuffer::set_clear_color;
				currentGPUAPI.frame_buffer_api.set_num_render_targets = vk::framebuffer::set_num_render_targets;

				// Texture 2D API
				currentGPUAPI.texture2D_api.create = vk::texture2D::create;
				currentGPUAPI.texture2D_api.destroy = vk::texture2D::destroy;
				currentGPUAPI.texture2D_api.set_debug_name = vk::texture2D::set_debug_name;

				// Texture CUBE API
				currentGPUAPI.textureCUBE_api.create = vk::textureCUBE::create;
				currentGPUAPI.textureCUBE_api.destroy = vk::textureCUBE::destroy;

				// Geometry API
				currentGPUAPI.geometry_api.create_vnt = vk::geometry::create_vnt;
				currentGPUAPI.geometry_api.destroy_vnt = vk::geometry::destroy_vnt;
				currentGPUAPI.geometry_api.draw = vk::geometry::draw;
				currentGPUAPI.geometry_api.set_bbox = vk::geometry::set_bbox;
				currentGPUAPI.geometry_api.bbox = vk::geometry::bbox;

				// Render Section API
				currentGPUAPI.render_section_api.start_render_section = vk::render_section::start_render_section;
				currentGPUAPI.render_section_api.end_render_section = vk::render_section::end_render_section;

				// Shader API
				currentGPUAPI.shader_api.create_shader = vk::shader::create_shader;
				currentGPUAPI.shader_api.create_shader_from_source = vk::shader::create_shader_from_source;
				currentGPUAPI.shader_api.destroy_shader = vk::shader::destroy_shader;

				currentGPUAPI.shader_api.bind_shader = vk::shader::bind_shader;
				currentGPUAPI.shader_api.unbind_shader = vk::shader::unbind_shader;

				currentGPUAPI.shader_api.inject_int = vk::shader::inject_int;
				currentGPUAPI.shader_api.inject_float = vk::shader::inject_float;
				currentGPUAPI.shader_api.inject_vec3 = vk::shader::inject_vec3;
				currentGPUAPI.shader_api.inject_vec4 = vk::shader::inject_vec4;
				currentGPUAPI.shader_api.inject_mat3 = vk::shader::inject_mat3;
				currentGPUAPI.shader_api.inject_mat4 = vk::shader::inject_mat4;

				currentGPUAPI.shader_api.inject_array = vk::shader::inject_array;

				currentGPUAPI.shader_api.inject_texture = vk::shader::inject_texture;

				currentGPUAPI.shader_api.inject_cubemap = vk::shader::inject_cubemap;

				// Make sure the default graphics settings are set
				currentGPUAPI.default_settings = vk::default_settings();
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
