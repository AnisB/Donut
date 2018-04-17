// Internal includes
#include "resource/texture.h"


namespace donut
{
	namespace texture
	{
		uint32_t pixel_size(const TTexture& target_texture)
		{
			return (uint8_t)target_texture.format * (uint8_t)target_texture.data_type;
		}

		void set_data(TTexture& target_texture, uint32_t width, uint32_t height, TTextureFormat::Type format, TTextureDataType::Type data_type)
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
			return target_texture.data.data() + p_height * target_texture.width * p_s + p_width * p_s;
		}

		const unsigned char* pixel(const TTexture& target_texture, uint32_t p_width, uint32_t p_height)
		{
			uint32_t p_s = pixel_size(target_texture);
			return target_texture.data.data() + p_height * target_texture.width * p_s + p_width * p_s;
		}
	}
}