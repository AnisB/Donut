#pragma once

// Internal includes
#include "texture.h"

namespace donut
{
	struct TSkybox
	{
		uint32_t							width;
		uint32_t							height;
		uint8_t								format;
		uint8_t								data_type;
		bento::Vector<unsigned char>		faces[6];

		TSkybox(bento::IAllocator& allocator)
		: width(0)
		, height(0)
		, faces {allocator, allocator, allocator, allocator, allocator, allocator}
		, format(0)
		, data_type(0)
		{
		}
	};

	namespace skybox
	{
		// Function that retuens the in-memory size of a pixel
		uint32_t pixel_size(const TSkybox& target_skybox);

		// Set the texture's data
		void set_data(TSkybox& target_texture, uint32_t width, uint32_t height, texture::TFormat::Type format, texture::TDataType::Type data_type);

		// Returns a pointer to the start of a pixel
		unsigned char* pixel(TSkybox& target_texture, uint32_t face_idx, uint32_t p_width, uint32_t p_height);
		const unsigned char* pixel(const TSkybox& target_texture, uint32_t face_idx, uint32_t p_width, uint32_t p_height);

		// Serialization functions
		void pack_bytes(bento::Vector<char>& buffer, const TSkybox& tex);
		bool unpack_bytes(const char*& stream, TSkybox& tex);

		// Build a skybox from a texture
		bool build_from_atlas(TSkybox& target_skybox, const TTexture& face_atlas);
	}
}