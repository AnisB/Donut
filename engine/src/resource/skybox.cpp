// Internal includes
#include "resource/skybox.h"

// Bento includes
#include <bento_base/stream.h>
#include <bento_base/log.h>

namespace donut
{
	namespace skybox
	{
		// Current version of the texture format
		const uint32_t SKYBOX_DATA_VERSION = 0;

		uint32_t pixel_size(const TSkybox& target_skybox)
		{
			return (uint8_t)target_skybox.format * (uint8_t)target_skybox.data_type;
		}

		void set_data(TSkybox& target_skybox, uint32_t width, uint32_t height, texture::TFormat::Type format, texture::TDataType::Type data_type)
		{
			target_skybox.width = width;
			target_skybox.height = height;
			target_skybox.format = format;
			target_skybox.data_type = data_type;
			for (uint32_t face_idx = 0; face_idx < 6; ++face_idx)
			{
				target_skybox.faces[face_idx].resize(width * height * (uint32_t)format * (uint32_t)data_type);
			}
		}

		unsigned char* pixel(TSkybox& target_skybox, uint32_t face_idx, uint32_t p_width, uint32_t p_height)
		{
			uint32_t p_s = pixel_size(target_skybox);
			return target_skybox.faces[face_idx].begin() + p_height * target_skybox.width * p_s + p_width * p_s;
		}

		const unsigned char* pixel(const TSkybox& target_skybox, uint32_t face_idx, uint32_t p_width, uint32_t p_height)
		{
			uint32_t p_s = pixel_size(target_skybox);
			return target_skybox.faces[face_idx].begin() + p_height * target_skybox.width * p_s + p_width * p_s;
		}

		bool build_from_atlas(TSkybox& target_skybox, const TTexture& face_atlas)
		{
			// We only support one type of cubemap for the moment
			if ((face_atlas.width * 3) == (face_atlas.height * 4))
			{
				// Compute the face resolution
				uint32_t cubemap_face_resolution = face_atlas.width / 4;

				set_data(target_skybox, cubemap_face_resolution, cubemap_face_resolution, (texture::TFormat::Type)face_atlas.format, (texture::TDataType::Type)face_atlas.data_type);

				// Prepare the textures for writing
				for (uint8_t face_idx = 0; face_idx < 6; ++face_idx)
				{
					// Shift values that allow us to define for each face where to read the face data
					uint32_t shift_w = 0;
					uint32_t shift_h = 0;

					if (face_idx == 0)
					{
						shift_w = 2 * cubemap_face_resolution;
						shift_h = cubemap_face_resolution;
					}
					else if(face_idx == 1)
					{
						shift_w = 0;
						shift_h = cubemap_face_resolution;
					}
					else if (face_idx == 2)
					{
						shift_w = cubemap_face_resolution;
						shift_h = 0;
					}
					else if (face_idx == 3)
					{
						shift_w = cubemap_face_resolution;
						shift_h =  2 * cubemap_face_resolution;
					}
					else if (face_idx == 4)
					{
						shift_w = cubemap_face_resolution;
						shift_h = cubemap_face_resolution;
					}
					else if (face_idx == 5)
					{
						shift_w = 3 * cubemap_face_resolution;
						shift_h = cubemap_face_resolution;
					}

					for (uint32_t h_idx = 0; h_idx < cubemap_face_resolution; ++h_idx)
					{
						for (uint32_t w_idx = 0; w_idx < cubemap_face_resolution; ++w_idx)
						{
							const unsigned char* source_pixel = texture::pixel(face_atlas, w_idx + shift_w, h_idx + shift_h);
							unsigned char* target_pixel = skybox::pixel(target_skybox, face_idx, w_idx, h_idx);
							memcpy(target_pixel, source_pixel, texture::pixel_size(face_atlas));
						}
					}
				}
				return true;
			}
			else
			{
				bento::default_logger()->log(bento::LogLevel::error, "RESOURCE", "Unsupported cubemap format");
				return false;
			}
		}

		void pack_bytes(bento::Vector<char>& buffer, const TSkybox& skybox)
		{
			bento::pack_bytes(buffer, SKYBOX_DATA_VERSION);
			bento::pack_bytes(buffer, skybox.width);
			bento::pack_bytes(buffer, skybox.height);
			bento::pack_bytes(buffer, skybox.format);
			bento::pack_bytes(buffer, skybox.data_type);
			for(uint32_t face_idx = 0; face_idx < 6; ++face_idx)
			{
				bento::pack_vector_bytes(buffer, skybox.faces[face_idx]);
			}
		}

		bool unpack_bytes(const char*& stream, TSkybox& skybox)
		{
			// Read the version
			uint32_t data_stream_version;
			bento::unpack_bytes(stream, data_stream_version);

			// Stop if this does not match the current version
			if (data_stream_version != SKYBOX_DATA_VERSION) return false;

			bento::unpack_bytes(stream, skybox.width);
			bento::unpack_bytes(stream, skybox.height);
			bento::unpack_bytes(stream, skybox.format);
			bento::unpack_bytes(stream, skybox.data_type);
			for(uint32_t face_idx = 0; face_idx < 6; ++face_idx)
			{
				bento::unpack_vector_bytes(stream, skybox.faces[face_idx]);
			}
			return true;
		}
	}
}