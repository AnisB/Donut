#pragma once

// Internal includes
#include "graphics/shader.h"
#include "graphics/shaderdata.h"
#include "gpu_backend/gpu_backend.h"
#include "resource/texture.h"
#include "core/box3.h"

namespace donut {
namespace gl {

	// Generic purpose functions
	void clear_state();
	bool check_state();

	// Force the rendering pipeline to execute
	void flush();

	// Window API
	namespace window
	{
		void show(RenderWindow window);
		void hide(RenderWindow window);
		bool is_active(RenderWindow window);
		void swap(RenderWindow window);
	}

	// Frame buffer API
	namespace framebuffer
	{
		// Frame buffer creation / destruction
		uint32_t create();
		void destroy(uint32_t frame_buffer);

		// Function to check a previously created frame buffer
		bool check();

		// Function to bind and unbind a frame buffer
		void bind(uint32_t frame_buffer);
		void unbind();

		// Bind a given texture
		void bind_texture(const TTextureInfo& _tex);

		// Depth test function
		void enable_depth_test(uint32_t frame_buffer);
		void disable_depth_test(uint32_t frame_buffer);

		// Framebuffer manipulation functions
		void clear(uint32_t frame_buffer);
		void set_clear_color(uint32_t frame_buffer, const bento::Vector4& _color);

		// Set the number of render targets for this render target
		void set_num_render_targets(uint8_t num_render_targets);
	}

	// Texture2D API
	namespace texture2D
	{
		// Texture creation / destruction
		void create(TTextureInfo& _tex, int width, int height);
		void destroy(TTextureInfo& _tex);
		void create(TTexture& source);
		void destroy(TTexture& source);
	}
	
	// TextureCUBE API
	namespace textureCUBE
	{
		void create(TSkyboxTexture& target_texture);
		void destroy(TSkyboxTexture& target_texture);
	}

	// Reading from currentFrameBuffer
	void ReadRGBFrameBuffer(int _width, int _length, unsigned char* _output);

	// Geometry API
	namespace geometry
	{
		// The possible function to create a geometry
		GeometryObject create_vnt(float* _dataArray, int _numVert, unsigned* _indexArray, int num_faces);
		void destroy_vnt(GeometryObject object);

		// Function to draw a given geometry
		void draw(GeometryObject geometry_object);

		// Functions to handle the bounding box
		void set_bbox(GeometryObject geometry, const TBox3& outbbox);
		void bbox(GeometryObject geometry, TBox3& outbbox);
	}

	#if 0
		#define GL_API_CHECK() {assert_msg_NO_RELEASE(check_state(), FUNCTION_NAME)}
	#else
		#define GL_API_CHECK() {}
	#endif
}
}