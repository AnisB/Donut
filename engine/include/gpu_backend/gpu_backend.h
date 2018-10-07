#pragma once

// Library includes
#include "settings.h"
#include "graphics/shaderdata.h"
#include "resource/texture.h"
#include "resource/skybox.h"
#include "resource/topping_descriptor.h"
#include "core/box3.h"

// Bento includes
#include "bento_math/types.h"

// External includes
#include <stdint.h>

namespace donut
{
	// Foward declare 
	struct TMaterial;

	struct GPURenderSystemAPI
	{
		bool (*init_render_system)();
		void (*shutdown_render_system)();

		RenderEnvironment (*create_render_environment)(const TGraphicSettings& graphic_settings);
		void (*destroy_render_environment)(RenderEnvironment render_environment);

		RenderWindow (*render_window)(RenderEnvironment _render);

		void (*collect_inputs)(RenderEnvironment render_environement);

		float (*get_time)(RenderEnvironment render_environement);
	};

	struct GPUWindowAPI
	{
		void (*show)(RenderWindow window);
		void (*hide)(RenderWindow window);
		bool (*is_active)(RenderWindow window);
		void (*swap)(RenderWindow window);
	};

	struct GPUFrameBufferAPI
	{
		FramebufferObject (*create)();
		void (*destroy)(FramebufferObject frame_buffer);

		// Function to check a previously created frame buffer
		bool (*check)(FramebufferObject framebuffer);

		// Function to bind and unbind a frame buffer
		void (*bind)(FramebufferObject framebuffer);
		void (*unbind)(FramebufferObject framebuffer);

		// Bind a given texture
		void (*bind_texture)(FramebufferObject framebuffer, const TTextureInfo& _tex);

		// Depth test function
		void (*enable_depth_test)(FramebufferObject framebuffer);
		void (*disable_depth_test)(FramebufferObject framebuffer);

		// Framebuffer manipulation functions
		void (*clear)(FramebufferObject frame_buffer);
		void (*set_clear_color)(FramebufferObject frame_buffer, const bento::Vector4& _color);

		// Set the number of render targets for this render target
		void (*set_num_render_targets)(FramebufferObject frmabuffer, uint8_t num_render_targets);
	};

	struct GPUTexture2DAPI
	{
		// Create a texture & Destroy it
		TextureObject (*create)(const TTexture& source);
		void (*destroy)(TextureObject tex);

		// Set debug name of a texture data
		void (*set_debug_name)(TextureObject texture, const char* debug_name);
	};

	struct GPUTextureCUBEAPI
	{
		CubemapObject (*create)(const TSkybox& source_skybox);
		void (*destroy)(CubemapObject cubemap);
	};

	struct GPUGeometryAPI
	{
		GeometryObject (*create_vnt)(const float* dataArray, uint32_t numVert, const unsigned* indexArray, uint32_t numFaces);
		void (*destroy_vnt)(GeometryObject object);

		void (*draw)(GeometryObject geometry_object);

		void (*set_bbox)(GeometryObject geometry, const TBox3& outbbox);
		void (*bbox)(GeometryObject geometry, TBox3& outbbox);
	};

	struct GPURenderSection
	{
		void (*start_render_section)(const char* sectionName);
		void (*end_render_section)();
	};

	struct GPUShaderAPI
	{
		ShaderPipelineObject (*create_shader)(const TShaderPipelineDescriptor& shader_pipeline);
		ShaderPipelineObject (*create_shader_from_source)(const char* vertex_shader_source, const char* tess_control_shader_source,
			const char* tess_eval_shader_source, const char* geometry_shader_source,
			const char* fragment_shader_source);
		void (*destroy_shader)(ShaderPipelineObject program);

		void (*bind_shader)(ShaderPipelineObject program);
		void (*unbind_shader)(ShaderPipelineObject program);

		void (*inject_int)(ShaderPipelineObject program, int value, const char* slot);
		void (*inject_float)(ShaderPipelineObject program, float value, const char* slot);
		void (*inject_vec3)(ShaderPipelineObject program, const bento::Vector3& value, const char* slot);
		void (*inject_vec4)(ShaderPipelineObject program, const bento::Vector4& value, const char* slot);
		void (*inject_mat3)(ShaderPipelineObject program, const bento::Matrix3& value, const char* slot);
		void (*inject_mat4)(ShaderPipelineObject program, const bento::Matrix4& value, const char* slot);

		void (*inject_array)(ShaderPipelineObject program, const float* value_array, uint32_t numValues, const char* slot);

		void (*inject_texture)(ShaderPipelineObject program, TextureObject texture_object, uint32_t offset, const char* slot);
		void (*inject_cubemap)(ShaderPipelineObject program, CubemapObject cubemap_object, uint32_t offset, const char* slot);
	};

	struct GPUBackendAPI
	{
		GPURenderSystemAPI render_system_api;
		GPUWindowAPI window_api;
		GPUFrameBufferAPI frame_buffer_api;
		GPUTexture2DAPI texture2D_api;
		GPUTextureCUBEAPI textureCUBE_api;
		GPURenderSection render_section_api;
		GPUGeometryAPI geometry_api;
		GPUShaderAPI shader_api;
		TGraphicSettings default_settings;
	};

	// Initialize the target api
	void initialize_gpu_backend(RenderingBackEnd::Type backend_type);

	// Request the target gpu API
	const GPUBackendAPI* gpu_api(RenderingBackEnd::Type backend_type);
}