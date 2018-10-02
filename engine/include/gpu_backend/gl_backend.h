#pragma once

// Library includes
#include "gpu_backend.h"

namespace donut
{
	namespace gl
	{
		namespace GLData
		{
			enum Type
			{
				ERROR_CALLBACK = 0,
				MAJOR_VERSION = 1,
				MINOR_VERSION = 2
 			};
		}

		// Builds and returns a default graphics setting for an opengl environement
		TGraphicSettings default_settings();

		namespace render_system
		{
			bool init_render_system();
			void shutdown_render_system();

			RenderEnvironment create_render_environment(const TGraphicSettings& graphic_settings);
			void destroy_render_environment(RenderEnvironment render_environment);

			RenderWindow render_window(RenderEnvironment render_environement);

			void collect_inputs(RenderEnvironment render_environement);

			float get_time(RenderEnvironment render_environement);
		}

		namespace window
		{
			void show(RenderWindow window);
			void hide(RenderWindow window);
			bool is_active(RenderWindow window);
			void swap(RenderWindow window);
		}

		namespace framebuffer
		{
			FramebufferObject create();
			void destroy(FramebufferObject frame_buffer);

			bool check(FramebufferObject framebuffer);

			void bind(FramebufferObject framebuffer);
			void unbind(FramebufferObject framebuffer);

			void bind_texture(FramebufferObject framebuffer, const TTextureInfo& _tex);

			void enable_depth_test(FramebufferObject framebuffer);
			void disable_depth_test(FramebufferObject framebuffer);

			void clear(FramebufferObject frame_buffer);
			void set_clear_color(FramebufferObject frame_buffer, const bento::Vector4& _color);

			void set_num_render_targets(FramebufferObject frmabuffer, uint8_t num_render_targets);
		}

		namespace texture2D
		{
			// Create and destroy textures
			TextureObject create(TTextureNature::Type nature, int width, int height);
			TextureObject create_color_texture(const TTexture& source);
			void destroy(TextureObject tex);

			// Set the debug name of the texture
			void set_debug_name(TextureObject texture, const char* debug_name);
		}

		namespace textureCUBE
		{
			CubemapObject create(const TSkybox& source_skybox);
			void destroy(CubemapObject cubemap);
		}

		namespace render_section
		{
			void start_render_section(const char* sectionName);
			void end_render_section();
		}
	}
}
