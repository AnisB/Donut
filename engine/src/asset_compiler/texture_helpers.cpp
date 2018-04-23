
// Bento includes
#include <bento_base/log.h>

// Engine includes
#include "asset_compiler/texture_helpers.h"
#include "gpu_backend/gl_factory.h"
#include "tools/lodepng.h"
 

// External includes
#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <stb_image.h>

namespace donut
{
	namespace TextureExtension
	{
		enum Type
		{
			JPG = 0,
			PNG = 1,
			BMP = 2,
			TGA = 3,
			COUNT = 4
		};
	}

	TextureExtension::Type GetImgType(const STRING_TYPE & parImg)
 	{
 		size_t stringLength = parImg.size();
 		const STRING_TYPE& extension = parImg.substr(parImg.find_last_of(".") + 1, stringLength - 1);
    	if(extension == "png")
    	{
    	    return TextureExtension::PNG;
    	}
    	else if(extension == "jpg" || extension == "jpeg")
    	{
    	    return TextureExtension::JPG;
    	}
    	else if(extension == "bmp")
    	{
    	    return TextureExtension::BMP;
    	}
    	else if(extension == "tga")
    	{
    	    return TextureExtension::TGA;
    	}
    	else 
    	{
	        return TextureExtension::COUNT;
	    }
	}

    STRING_TYPE ImgTypeToString(TextureExtension::Type parType)
    {
        switch(parType)
        {
            case TextureExtension::PNG:
                return ".png";
            case TextureExtension::BMP:
                return ".bmp";
            case TextureExtension::JPG:
                return ".jpg";
            case TextureExtension::TGA:
                return ".tga";
            default:
                return "";
            break;
        };
    }

    void read_bmp(const char * path_name, TTexture& output_texture )
    {
		if (path_name == nullptr)
		{
			bento::default_logger()->log(bento::LogLevel::error, "RESOURCE", "Invalid texture path");
			return;
		}

#if __posix__
        FILE* f = fopen(Filename, "rb");
#elif WIN32
        FILE* f = NULL;
		fopen_s(&f, path_name, "rb");
#endif
        assert(f);

        unsigned char info[54];
        fread(info, sizeof(unsigned char), 54, f); // read the 54-byte header

        // Extract the data from the texture
        uint32_t w = *(int*)&info[18];
		uint32_t h = *(int*)&info[22];
		uint32_t data_size = 3 * w  * h;

		// Prepare the texture for writing
		output_texture.width = w;
		output_texture.height = h;
		output_texture.data_type = texture::TDataType::UNSIGNED_BYTE;
		output_texture.format = texture::TFormat::RGB;
		output_texture.data.resize(data_size);

		unsigned char* data = output_texture.data.begin(); // allocate 3 bytes per pixel
        fread(data, sizeof(unsigned char), data_size, f); // read the rest of the data at once
        fclose(f);

        for(uint32_t i = 0; i < data_size; i += 3)
        {
                unsigned char tmp = data[i];
                data[i] = data[i+2];
                data[i+2] = tmp;
        }

		int shift = *(int*)&info[14];
		shift /= 3;
		unsigned char* tampon = new unsigned char[w*3];
		for (uint32_t i = 0; i < h; ++i)
		{
			memcpy(tampon, data + i*w * 3 + shift * 3, (w - shift) * 3);
			memcpy(tampon + (w - shift) * 3, data, shift * 3);
			memcpy(data + i * w * 3, tampon, w * 3);
		}
		delete [] tampon;
    }

	void read_jpg(const char* texture_path, TTexture& texture)
	{
		// Components per pixel.
		int cpp;

		// Ask for always four components per pixels: RGBA
		int width, height;
		unsigned char *data = stbi_load(texture_path, &width, &height, &cpp, 3);

		if (data == nullptr) 
		{
			return;
		}

		// Resize the texture 
		texture::set_data(texture, width, height, texture::TFormat::RGB, texture::TDataType::UNSIGNED_BYTE);

		// Copy the read data
		memcpy(texture.data.begin(), data, texture.data.size());

		// Free the memory
		stbi_image_free(data);
	}


    void read_tga(const char* file_name, TTexture& output_texture)
    {
        std::fstream hFile(file_name, std::ios::in | std::ios::binary);

        if (!hFile.is_open())
        {
            assert_fail_msg("File not found");
            return;
        }
        
        std::uint8_t Header[18] = {0};
        static std::uint8_t DeCompressed[12] = {0x0, 0x0, 0x2, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0};
        static std::uint8_t IsCompressed[12] = {0x0, 0x0, 0xA, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0};

        hFile.read(reinterpret_cast<char*>(&Header), sizeof(Header));

        if (!memcmp(DeCompressed, &Header, sizeof(DeCompressed)))
        {
            int BitsPerPixel = Header[16];
            int width  = Header[13] * 0xFF + Header[12];
            int height = Header[15] * 0xFF + Header[14];
            int data_size  = ((width * BitsPerPixel + 31) / 32) * 4 * height;

			output_texture.width = width;
			output_texture.height = height;
			output_texture.data_type = texture::TDataType::UNSIGNED_BYTE;

            switch(BitsPerPixel)
            {
                case 24:
					output_texture.format = texture::TFormat::RGB;
                break;
                case 32:
					output_texture.format = texture::TFormat::RGBA;
                break;
                default: 
                    hFile.close();
                    assert_fail_msg("Invalid File Format. Required: 24 or 32 Bit Image.");
            }

			output_texture.data.resize(data_size);
            hFile.read(reinterpret_cast<char*>(output_texture.data.begin()), data_size);
        }
        else
        {
            hFile.close();
            assert_fail_msg("Invalid File Format. Required: 24 or 32 Bit TGA File.");
            return;
        }
        hFile.close();
    }

	void read_png(const char* texture_path, TTexture& texture)
	{
		unsigned char *image = nullptr;
		unsigned int width;
		unsigned int height;

		unsigned int ret = lodepng_decode32_file(&image, &width, &height, texture_path);

		if (ret != 0)
		{
			if (image)
				free(image);
			return ;
		}

		// Resize the texture 
		texture::set_data(texture, width, height, texture::TFormat::RGBA, texture::TDataType::UNSIGNED_BYTE);

		// Copy the read data
		memcpy(texture.data.begin(), image, texture.data.size());

		// Free the allocated buffer
		free(image);
	}

	void LoadTexture(const char* path_source, TTexture& output_texture)
 	{
		TextureExtension::Type typeImg = GetImgType(path_source);

	    switch (typeImg)
	    {
	    	case TextureExtension::PNG:
                read_png(path_source, output_texture);
	    	    break;
	    	case TextureExtension::JPG:
	    	    read_jpg(path_source, output_texture);

	    	    break;
	    	case TextureExtension::BMP:
	    	    read_bmp(path_source, output_texture);
	    	    break;
	    	case TextureExtension::TGA:
	    	    read_tga(path_source, output_texture);
	    	    break;
    	    default:
    	        assert_fail_msg("Unhandled type");
	    };
	}

    namespace TSkyboxComponent
    {
        enum Type
        {
            PX,
            NX,
            PY,
            NY,
            PZ,
            NZ
        };
    }
    STRING_TYPE SkyboxComponentToString(TSkyboxComponent::Type parType)
    {
        switch(parType)
        {
            case TSkyboxComponent::PX:
                return "/px";
            case TSkyboxComponent::NX:
                return "/nx";
            case TSkyboxComponent::PY:
                return "/py";
            case TSkyboxComponent::NY:
                return "/ny";
            case TSkyboxComponent::PZ:
                return "/pz";
            case TSkyboxComponent::NZ:
                return "/nz";
        };
        return "";
    }
    
    STRING_TYPE ConcatFileName(const STRING_TYPE& parFolderName,TSkyboxComponent::Type parType, TextureExtension::Type parImgType )
    {
        STRING_TYPE filename(parFolderName);
        filename += SkyboxComponentToString(parType);
        filename += ImgTypeToString(parImgType);
        return filename;
    }

	void LoadSkybox(const char* path_source, TSkybox& output_skybox)
	{
		// Read the combined texture
		TTexture combined_texture(*bento::common_allocator());
		LoadTexture(path_source, combined_texture);

		// We only support one type of cubemap for the moment
		if ((combined_texture.width * 3) == (combined_texture.height * 4))
		{
			// Compute the face resolution
			uint32_t cubemap_face_resolution = combined_texture.width / 4;

			// Set the skybox data
			skybox::set_data(output_skybox, cubemap_face_resolution, cubemap_face_resolution, (texture::TFormat::Type)combined_texture.format, (texture::TDataType::Type)combined_texture.data_type);

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
						unsigned char* source_pixel = texture::pixel(combined_texture, w_idx + shift_w, h_idx + shift_h);
						unsigned char* target_pixel = skybox::pixel(output_skybox, face_idx, w_idx, h_idx);
						memcpy(target_pixel, source_pixel, texture::pixel_size(combined_texture));
					}
				}
			}
		}
		else
		{
			bento::default_logger()->log(bento::LogLevel::error, "RESOURCE", "Unsupported cubemap format");
		}
    }
}