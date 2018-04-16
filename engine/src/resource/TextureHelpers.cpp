
// Bento includes
#include <bento_base/log.h>

// Engine includes
#include "gpu_backend/gl_factory.h"
#include "resource/TextureHelpers.h"
 

// External includes
#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <jpeglib.h>
#include <jerror.h>
#if __posix__
#include <png.h>
#elif WIN32
#endif

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
		output_texture.data_type = TTextureDataType::UNSIGNED_BYTE;
		output_texture.format = TTextureFormat::RGB;
		output_texture.data.resize(data_size);

		unsigned char* data = output_texture.data.data(); // allocate 3 bytes per pixel
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
    void read_jpg(const char* file_path, TTexture& output_texture)
    {
        FILE* file = fopen(file_path, "rb");  //open the file
        struct jpeg_decompress_struct info;  //the jpeg decompress info
        struct jpeg_error_mgr err;           //the error handler

        info.err = jpeg_std_error(&err);     //tell the jpeg decompression handler to send the errors to err
        jpeg_create_decompress(&info);       //sets info to all the default stuff

        //if the jpeg file didnt load exit
        if(!file)
        {
			bento::default_logger()->log(bento::LogLevel::error, "RESOURCE", "Failed to load texture");
            return;
        }
		output_texture.file_path = file_path;

        jpeg_stdio_src(&info, file);    //tell the jpeg lib the file we'er reading

        jpeg_read_header(&info, TRUE);   //tell it to start reading it

        jpeg_start_decompress(&info);    //decompress the file

        // Read the texture data
		uint32_t w = info.output_width;
		uint32_t h = info.output_height;
		uint32_t num_pixels = w * h;
		uint32_t data_size = w * h * 3;

		// Prepare the texture for writing
		output_texture.width = w;
		output_texture.height = h;
		output_texture.data_type = TTextureDataType::UNSIGNED_BYTE;
		output_texture.format = TTextureFormat::RGB;
		output_texture.data.resize(data_size);

        uint32_t channels = info.num_components;
		uint32_t type = 0x1907;
        if(channels == 4)
        {
            type = 0x1908;
        }

		uint32_t bpp = channels * 8;

        unsigned char* p1 = (unsigned char*)output_texture.data.data();
        unsigned char** p2 = &p1;
        int numlines = 0;

        while(info.output_scanline < info.output_height)
        {
            numlines = jpeg_read_scanlines(&info, p2, 1);
            *p2 += numlines * 3 * info.output_width;
        }

        jpeg_finish_decompress(&info);   //finish decompressing this file

        fclose(file);                    //close the file
    }

    TTexture* LoadPNG(const char* file_name, TTexture& output_texture)
    {
#if __posix__
        png_byte header[8];

        FILE *fp = fopen(file_name, "rb");
        if (fp == 0)
        {
            perror(file_name);
            assert_fail_msg("File not found: "<<file_name);
            return 0;
        }

        // read the header
        fread(header, 1, 8, fp);

        if (png_sig_cmp(header, 0, 8))
        {
            assert_fail_msg("File is not a PNG: "<<file_name);
            fclose(fp);
            return 0;
        }

        png_structp png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
        if (!png_ptr)
        {
            assert_fail_msg("png_create_read_struct returned 0");
            fclose(fp);
            return 0;
        }

        // create png info struct
        png_infop info_ptr = png_create_info_struct(png_ptr);
        if (!info_ptr)
        {
            fprintf(stderr, "error: png_create_info_struct returned 0.\n");
            png_destroy_read_struct(&png_ptr, (png_infopp)NULL, (png_infopp)NULL);
            fclose(fp);
            return 0;
        }

        // create png info struct
        png_infop end_info = png_create_info_struct(png_ptr);
        if (!end_info)
        {
            fprintf(stderr, "error: png_create_info_struct returned 0.\n");
            png_destroy_read_struct(&png_ptr, &info_ptr, (png_infopp) NULL);
            fclose(fp);
            return 0;
        }

        // the code in this if statement gets called if libpng encounters an error
        if (setjmp(png_jmpbuf(png_ptr))) {
            fprintf(stderr, "error from libpng\n");
            png_destroy_read_struct(&png_ptr, &info_ptr, &end_info);
            fclose(fp);
            return 0;
        }

        // init png reading
        png_init_io(png_ptr, fp);

        // let libpng know you already read the first 8 bytes
        png_set_sig_bytes(png_ptr, 8);

        // read all the info up to the image data
        png_read_info(png_ptr, info_ptr);

        // variables to pass to get info
        int bit_depth, color_type;
        png_uint_32 temp_width, temp_height;

        // get info about png
        png_get_IHDR(png_ptr, info_ptr, &temp_width, &temp_height, &bit_depth, &color_type,
            NULL, NULL, NULL);

        TTexture* image = new TTexture(file_name,TImgType::PNG, temp_width, temp_height);
        image->FFormat = GL_RGBA;

        // Update the png info struct.
        png_read_update_info(png_ptr, info_ptr);

        // Row size in bytes.
        int rowbytes = png_get_rowbytes(png_ptr, info_ptr);

        // glTexImage2d requires rows to be 4-byte aligned
        rowbytes += 3 - ((rowbytes-1) % 4);

        // Allocate the image_data as a big block, to be given to opengl
        png_byte * image_data;
        image_data = (unsigned char*)malloc(rowbytes * temp_height * sizeof(png_byte)+15);
        if (image_data == NULL)
        {
            fprintf(stderr, "error: could not allocate memory for PNG image data\n");
            png_destroy_read_struct(&png_ptr, &info_ptr, &end_info);
            fclose(fp);
            return 0;
        }

        // row_pointers is for pointing to image_data for reading the png with libpng
        png_bytep * row_pointers = (unsigned char**)(malloc(temp_height * sizeof(png_bytep)));
        if (row_pointers == NULL)
        {
            fprintf(stderr, "error: could not allocate memory for PNG row pointers\n");
            png_destroy_read_struct(&png_ptr, &info_ptr, &end_info);
            free(image_data);
            fclose(fp);
            return 0;
        }

        // set the individual row_pointers to point at the correct offsets of image_data
        int i;
        for (i = 0; i < temp_height; i++)
        {
            row_pointers[temp_height - 1 - i] = image_data + i * rowbytes;
        }

        // read the png into image_data through row_pointers
        png_read_image(png_ptr, row_pointers);

        image->FData = image_data;
        // clean up
        png_destroy_read_struct(&png_ptr, &info_ptr, &end_info);
        free(row_pointers);
        fclose(fp);
        return image;
#elif WIN32
		assert_fail();
		return nullptr;
#endif
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
			output_texture.data_type = TTextureDataType::UNSIGNED_BYTE;

            switch(BitsPerPixel)
            {
                case 24:
					output_texture.format = TTextureFormat::RGB;
                break;
                case 32:
					output_texture.format = TTextureFormat::RGBA;
                break;
                default: 
                    hFile.close();
                    assert_fail_msg("Invalid File Format. Required: 24 or 32 Bit Image.");
            }

			output_texture.data.resize(data_size);
            hFile.read(reinterpret_cast<char*>(output_texture.data.data()), data_size);
        }
        else
        {
            hFile.close();
            assert_fail_msg("Invalid File Format. Required: 24 or 32 Bit TGA File.");
            return;
        }
        hFile.close();
    }

	void LoadTexture(const char* path_source, TTexture& output_texture)
 	{
		TextureExtension::Type typeImg = GetImgType(path_source);

	    switch (typeImg)
	    {
	    	case TextureExtension::PNG:
                LoadPNG(path_source, output_texture);
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

    TSkyboxTexture* LoadSkybox(const STRING_TYPE&  skybox_source)
    {
		// Read the combined texture
		TTexture combined_texture;
		LoadTexture(skybox_source.c_str(), combined_texture);

		// Create the structure that will host the cubemap
		TSkyboxTexture * skybox = new TSkyboxTexture();
		skybox->file_path = skybox_source;

		// We only support one type of cubemap for the moment
		if ((combined_texture.width * 3) == (combined_texture.height * 4))
		{
			// Compute the face resolution
			uint32_t cubemap_face_resolution = combined_texture.width / 4;

			// Prepare the textures for writing
			for (uint8_t face_idx = 0; face_idx < 6; ++face_idx)
			{
				// Set the data and allocate the memory space
				TTexture& current_face = skybox->faces[face_idx];
				current_face.width = cubemap_face_resolution;
				current_face.height = cubemap_face_resolution;
				current_face.format = combined_texture.format;
				current_face.data_type = combined_texture.data_type;
				current_face.data.resize(current_face.width * current_face.height * (uint8_t)current_face.format * (uint8_t)current_face.data_type);
			
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
						unsigned char* target_pixel = texture::pixel(current_face, w_idx, h_idx);
						memcpy(target_pixel, source_pixel, texture::pixel_size(combined_texture));
					}
				}
			}
		}
		else
		{
			bento::default_logger()->log(bento::LogLevel::error, "RESOURCE", "Unsupported cubemap format");
			delete skybox;
			return nullptr;
		}
        return skybox;
    }

    void TakeScreenShot(const STRING_TYPE& parFileName)
    {
#if __posix__
        unsigned char *pdata = new unsigned char[1280*720*3];

        ReadRGBFrameBuffer(1280, 720, pdata);
        FILE *outfile;

        if ((outfile = fopen(parFileName.c_str(), "wb")) == NULL) 
        {
            printf("can't open %s",parFileName.c_str());
            return;
        }

        struct jpeg_compress_struct cinfo;
        struct jpeg_error_mgr       jerr;

        cinfo.err = jpeg_std_error(&jerr);
        jpeg_create_compress(&cinfo);
        jpeg_stdio_dest(&cinfo, outfile);

        cinfo.image_width      = 1280;
        cinfo.image_height     = 720;
        cinfo.input_components = 3;
        cinfo.in_color_space   = JCS_RGB;

        jpeg_set_defaults(&cinfo);
        /*set the quality [0..100]  */
        jpeg_set_quality (&cinfo, 100, true);
        jpeg_start_compress(&cinfo, true);

        JSAMPROW row_pointer;
        int row_stride = 1280 * 3;

        while (cinfo.next_scanline < cinfo.image_height)
        {
            row_pointer = (JSAMPROW) &pdata[(cinfo.image_height-1-cinfo.next_scanline)*row_stride];
            jpeg_write_scanlines(&cinfo, &row_pointer, 1);
        }
#elif WIN32
		assert_fail();
#endif
    }

    void SaveTextureToFile(const STRING_TYPE& parFileName, const TTexture* parTexture)
    {
#if __posix__
        float *pdata = (float*)(parTexture->FData);

        FILE *outfile;
        if ((outfile = fopen(parFileName.c_str(), "wb")) == NULL) 
        {
            printf("can't open %s",parFileName.c_str());
            return;
        }

        struct jpeg_compress_struct cinfo;
        struct jpeg_error_mgr       jerr;

        cinfo.err = jpeg_std_error(&jerr);
        jpeg_create_compress(&cinfo);
        jpeg_stdio_dest(&cinfo, outfile);

        cinfo.image_width      = 1280;
        cinfo.image_height     = 720;
        cinfo.input_components = 3;
        cinfo.in_color_space   = JCS_RGB;

        jpeg_set_defaults(&cinfo);
        /*set the quality [0..100]  */
        jpeg_set_quality (&cinfo, 100, true);
        jpeg_start_compress(&cinfo, true);

        JSAMPROW row_pointer;
        int row_stride = 1280 * 3;

        while (cinfo.next_scanline < cinfo.image_height)
        {
            row_pointer = (JSAMPROW) &pdata[(cinfo.image_height-1-cinfo.next_scanline)*row_stride];
            jpeg_write_scanlines(&cinfo, &row_pointer, 1);
        }
#elif WIN32
		assert_fail();
#endif
    }
}