#pragma once

// Library includes
#include "gpu_backend.h"

namespace donut
{
	namespace gl
	{
		void clear_state();
		bool check_state();

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
			TextureObject create(const TTexture& source);
			void destroy(TextureObject tex);

			// Set the debug name of the texture
			void set_debug_name(TextureObject texture, const char* debug_name);
		}

		namespace textureCUBE
		{
			CubemapObject create(const TSkybox& source_skybox);
			void destroy(CubemapObject cubemap);
		}

		namespace geometry
		{
			GeometryObject create_vnt(const float* dataArray, uint32_t numVert, const unsigned* indexArray, uint32_t numFaces);
			void destroy_vnt(GeometryObject object);

			void draw(GeometryObject geometry_object);

			void set_bbox(GeometryObject geometry, const TBox3& outbbox);
			void bbox(GeometryObject geometry, TBox3& outbbox);
		}

		namespace shader
		{
			ShaderPipelineObject create_shader(const TShaderPipelineDescriptor& shader_pipeline);
			ShaderPipelineObject create_shader_from_source(const char* vertex_shader_source, const char* tess_control_shader_source,
													const char* tess_eval_shader_source, const char* geometry_shader_source, 
													const char* fragment_shader_source);
			void destroy_shader(ShaderPipelineObject program);

	 		void bind_shader(ShaderPipelineObject program);
	 		void unbind_shader(ShaderPipelineObject program);

	 		void inject_int(ShaderPipelineObject program, int value, const char* slot);
	 		void inject_float(ShaderPipelineObject program, float value, const char* slot);
	 		void inject_vec3(ShaderPipelineObject program, const bento::Vector3& value, const char* slot);
	 		void inject_vec4(ShaderPipelineObject program, const bento::Vector4& value, const char* slot);
	 		void inject_mat3(ShaderPipelineObject program, const bento::Matrix3& value, const char* slot);
	 		void inject_mat4(ShaderPipelineObject program, const bento::Matrix4& value, const char* slot);

			void inject_array(ShaderPipelineObject program, const float* value_array, uint32_t numValues, const char* slot);

			void inject_texture(ShaderPipelineObject program, TextureObject texture_object, uint32_t offset, const char* slot);
			void inject_cubemap(ShaderPipelineObject program, CubemapObject cubemap_object, uint32_t offset, const char* slot);
		}

		namespace render_section
		{
			void start_render_section(const char* sectionName);
			void end_render_section();
		}

	#if 1
		#define GL_API_CHECK() {assert_msg(gl::check_state(), FUNCTION_NAME);}
	#else
		#define GL_API_CHECK() {}
	#endif
	}
}
