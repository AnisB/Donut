#pragma once

// External includes
#include <string>
#include <vector>

namespace donut
{
	namespace TTextureFormat
	{
		enum Type
		{
			RGB = 3,
			RGBA = 4,
			NONE
		};
	}

	namespace TTextureDataType
	{
		enum Type
		{
			UNSIGNED_BYTE = 1,
			FLOAT = 8
		};
	}

	struct TTexture
	{
		// The texture's data
		uint32_t					tex_id;
		uint32_t					width;
		uint32_t					height;
		TTextureFormat::Type		format;
		TTextureDataType::Type		data_type;
		std::vector<unsigned char>  data;

		// Source file of the texture
		std::string					file_path;

		TTexture()
			: width(0)
			, height(0)
			, data()
			, file_path("")
			, format(TTextureFormat::RGBA)
			, data_type(TTextureDataType::UNSIGNED_BYTE)
		{
		}
	};

	namespace texture
	{
		// Function that retuens the in-memory size of a pixel
		uint32_t pixel_size(const TTexture& target_texture);

		// Returns a pointer to the start of a pixel
		unsigned char* pixel(TTexture& target_texture, uint32_t p_width, uint32_t p_height);
		const unsigned char* pixel(const TTexture& target_texture, uint32_t p_width, uint32_t p_height);
	}

	struct TSkyboxTexture
	{
		uint32_t		tex_id;
		TTexture        faces[6];
		std::string     file_path;

		TSkyboxTexture()
			: file_path("")
			, tex_id(0)
		{
		}
	};
}
