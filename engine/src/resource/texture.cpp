// Internal includes
#include "resource/texture.h"

// Bento includes
#include <bento_base/stream.h>


namespace donut
{
	// Current version of the texture format
	const uint32_t TEXTURE_DATA_VERSION = 0;

	namespace texture
	{
		uint32_t pixel_size(const TTexture& target_texture)
		{
			return (uint8_t)target_texture.format * (uint8_t)target_texture.data_type;
		}

		void set_data(TTexture& target_texture, uint32_t width, uint32_t height, texture::TFormat::Type format, texture::TDataType::Type data_type)
		{
			target_texture.width = width;
			target_texture.height = height;
			target_texture.format = format;
			target_texture.data_type = data_type;
			target_texture.data.resize(width * height * (uint32_t)format * (uint32_t)data_type);
		}

		unsigned char* pixel(TTexture& target_texture, uint32_t p_width, uint32_t p_height)
		{
			uint32_t p_s = pixel_size(target_texture);
			return target_texture.data.begin() + p_height * target_texture.width * p_s + p_width * p_s;
		}

		const unsigned char* pixel(const TTexture& target_texture, uint32_t p_width, uint32_t p_height)
		{
			uint32_t p_s = pixel_size(target_texture);
			return target_texture.data.begin() + p_height * target_texture.width * p_s + p_width * p_s;
		}
	}
}

namespace bento
{
	void pack_type(bento::Vector<char>& buffer, const donut::TTexture& tex)
	{
		bento::pack_bytes(buffer, donut::TEXTURE_DATA_VERSION);
		bento::pack_bytes(buffer, tex.width);
		bento::pack_bytes(buffer, tex.height);
		bento::pack_bytes(buffer, tex.format);
		bento::pack_bytes(buffer, tex.data_type);
		bento::pack_vector_bytes(buffer, tex.data);
	}

	bool unpack_type(const char*& stream, donut::TTexture& tex)
	{
		// Read the version
		uint32_t data_stream_version;
		bento::unpack_bytes(stream, data_stream_version);

		// Stop if this does not match the current version
		if (data_stream_version != donut::TEXTURE_DATA_VERSION) return false;

		bento::unpack_bytes(stream, tex.width);
		bento::unpack_bytes(stream, tex.height);
		bento::unpack_bytes(stream, tex.format);
		bento::unpack_bytes(stream, tex.data_type);
		bento::unpack_vector_bytes(stream, tex.data);
		return true;
	}
}