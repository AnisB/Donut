#pragma once

// Bento include
#include <bento_collection/vector.h>

namespace donut
{
	struct TTexture
	{
		uint32_t						width;
		uint32_t						height;
		uint8_t							format;
		uint8_t	    					data_type;
		bento::Vector<unsigned char>  	data;

		TTexture(bento::IAllocator& allocator)
		: width(0)
		, height(0)
		, data(allocator)
		, format(0)
		, data_type(0)
		{
		}
	};

	namespace texture
	{
		namespace TFormat
		{
			enum Type
			{
				DEPTH = 1,
				RGB = 3,
				RGBA = 4,
				NONE = 0
			};
		}

		namespace TDataType
		{
			enum Type
			{
				UNSIGNED_BYTE = 1,
				DEPTH = 2,
				FLOAT = 8,
				NONE = 0
			};
		}

		// Function that retuens the in-memory size of a pixel
		uint32_t pixel_size(const TTexture& target_texture);

		// Set the texture's data
		void set_data(TTexture& target_texture, uint32_t width, uint32_t height, TFormat::Type format, TDataType::Type data_type);

		// Returns a pointer to the start of a pixel
		unsigned char* pixel(TTexture& target_texture, uint32_t p_width, uint32_t p_height);
		const unsigned char* pixel(const TTexture& target_texture, uint32_t p_width, uint32_t p_height);
	}
}

namespace bento
{
	void pack_type(bento::Vector<char>& buffer, const donut::TTexture& tex);
	bool unpack_type(const char*& stream, donut::TTexture& tex);
}