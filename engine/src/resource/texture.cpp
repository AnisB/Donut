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