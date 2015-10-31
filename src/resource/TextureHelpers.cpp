/**
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as
 * published by the Free Software Foundation, either version 3 of the
 * License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 *
 **/

#include <base/common.h>
#include <render/Common.h>
#include <input/Common.h>
#include <resource/Common.h>
#include "TextureHelpers.h"
 
#include <stdio.h>
#include <stdlib.h>
#if __posix__
#include <jpeglib.h>
#include <jerror.h>
#include <png.h>
#elif WIN32
#endif
namespace Donut
{

 namespace TextureHelpers
 {
 	TImgType::Type GetImgType(const std::string & parImg)
 	{
 		size_t stringLength = parImg.size();
 		const std::string& extension = parImg.substr(parImg.find_last_of(".") + 1, stringLength - 1);
    	if(extension == "png")
    	{
    	    return TImgType::PNG;
    	}
    	else if(extension == "jpg" || extension == "jpeg")
    	{
    	    return TImgType::JPG;
    	}
    	else if(extension == "bmp")
    	{
    	    return TImgType::BMP;
    	}
    	else if(extension == "tga")
    	{
    	    return TImgType::TGA;
    	}
    	else 
    	{
	        return TImgType::NONE;
	    }
	}

    std::string ImgTypeToString(TImgType::Type parType)
    {
        switch(parType)
        {
            case TImgType::PNG:
                return ".png";
            case TImgType::BMP:
                return ".bmp";
            case TImgType::JPG:
                return ".jpg";
            default:
                return "";
            break;
        };
    }
    GLuint CreateTextureCube()
    {
        GLuint texID;   
        glGenTextures(1, &texID);
        glBindTexture(GL_TEXTURE_CUBE_MAP, texID);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_BASE_LEVEL, 0); 
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAX_LEVEL, 0); 
        return texID;
    }

    void BindToCubeMap(GLuint parType, TTexture* parTexture)
    {
        glTexImage2D(parType, 0, GL_RGBA8, parTexture->FWidth, parTexture->FHeight, 0, GL_BGRA, GL_UNSIGNED_BYTE, parTexture->FData);
    }

    TTexture* LoadBMP(const char *Filename )
    {
        if( !Filename )
            return NULL;

#if __posix__
        FILE* f = fopen(Filename, "rb");
#elif WIN32
        FILE* f = NULL;
		fopen_s(&f, Filename, "rb");
#endif
        if(f==NULL)
        {
            INPUT_ERROR("Erreur ouverture fichier "<<Filename);  
            return NULL;  
        }
        unsigned char info[54];
        fread(info, sizeof(unsigned char), 54, f); // read the 54-byte header

        // extract image height and width from header
        int w = *(int*)&info[18];
        int l = *(int*)&info[22];

        TTexture* Image = new TTexture(Filename,TImgType::BMP, w, l );

        int size = 3 * w  * l ;
        unsigned char* data = new unsigned char[size]; // allocate 3 bytes per pixel
        fread(data, sizeof(unsigned char), size, f); // read the rest of the data at once
        fclose(f);

        for(int i = 0; i < size; i += 3)
        {
                unsigned char tmp = data[i];
                data[i] = data[i+2];
                data[i+2] = tmp;
        }

        // read the data.
        Image->FData = data;
        return Image;
    }
    TTexture* LoadJPG(const char* FileName, bool Fast = true)
    {
#if __posix__
        // printf("Loading jpg dude %s\n", FileName);

        FILE* file = fopen(FileName, "rb");  //open the file
        struct jpeg_decompress_struct info;  //the jpeg decompress info
        struct jpeg_error_mgr err;           //the error handler

        info.err = jpeg_std_error(&err);     //tell the jpeg decompression handler to send the errors to err
        jpeg_create_decompress(&info);       //sets info to all the default stuff

        //if the jpeg file didnt load exit
        if(!file)
        {
            fprintf(stderr, "Error reading JPEG file %s!!!", FileName);
            return NULL;
        }

        jpeg_stdio_src(&info, file);    //tell the jpeg lib the file we'er reading

        jpeg_read_header(&info, TRUE);   //tell it to start reading it

        //if it wants to be read fast or not
        if(Fast)
        {
            info.do_fancy_upsampling = FALSE;
        }

        jpeg_start_decompress(&info);    //decompress the file

        //set the x and y
        unsigned int w = info.output_width;
        unsigned int l = info.output_height;
        TTexture* Image = new TTexture(FileName,TImgType::JPG, w, l );
        GLuint channels = info.num_components;

        GLuint type = GL_RGB;

        if(channels == 4)
        {
            type = GL_RGBA;
        }

        GLuint bpp = channels * 8;

        GLuint size = w * l * 3;

        //read turn the uncompressed data into something ogl can read
        Image->FData = new unsigned char[size];      //setup data for the data its going to be handling

        unsigned char* p1 = (unsigned char*)    Image->FData;
        unsigned char** p2 = &p1;
        int numlines = 0;

        while(info.output_scanline < info.output_height)
        {
            numlines = jpeg_read_scanlines(&info, p2, 1);
            *p2 += numlines * 3 * info.output_width;
        }

        jpeg_finish_decompress(&info);   //finish decompressing this file

        fclose(file);                    //close the file

        return Image;
#elif WIN32
		ASSERT_NOT_IMPLEMENTED()
		return nullptr;

#endif
    }

    TTexture* LoadPNG(const char* file_name)
    {
#if __posix__
        png_byte header[8];

        FILE *fp = fopen(file_name, "rb");
        if (fp == 0)
        {
            perror(file_name);
            ASSERT_FAIL_MSG("File not found: "<<file_name);
            return 0;
        }

        // read the header
        fread(header, 1, 8, fp);

        if (png_sig_cmp(header, 0, 8))
        {
            ASSERT_FAIL_MSG("File is not a PNG: "<<file_name);
            fclose(fp);
            return 0;
        }

        png_structp png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
        if (!png_ptr)
        {
            ASSERT_FAIL_MSG("png_create_read_struct returned 0");
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
		ASSERT_NOT_IMPLEMENTED()
		return nullptr;
#endif
    }

 	TTexture * LoadTexture(const std::string & parImg)
 	{
 		TImgType::Type typeImg = GetImgType(parImg);

 		TTexture * texture = NULL;
	    switch (typeImg)
	    {
	    	case TImgType::PNG:
                texture = LoadPNG(parImg.c_str());
	    	    break;
	    	case TImgType::JPG:
	    	    texture = LoadJPG(parImg.c_str());

	    	    break;
	    	case TImgType::BMP:
	    	    texture = LoadBMP(parImg.c_str());

	    	    break;
	    	case TImgType::TGA:
	    	    texture = NULL;
	    	    break;
    	    default:
    	        ASSERT_FAIL_MSG("Unhandled type "<<parImg);
	    };
	    return texture;
	}

    void CreateTexture(TTexture* parTex)
    {
        RESOURCE_INFO("Creating GPU texture.");
        glGenTextures(1, &(parTex->FID));
        glBindTexture(GL_TEXTURE_2D, parTex->FID);

        if(parTex->FType == TImgType::PNG || parTex->FType == TImgType::TGA)
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, parTex->FWidth, parTex->FHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, parTex->FData);
        if(parTex->FType == TImgType::BMP || parTex->FType == TImgType::JPG)
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, parTex->FWidth, parTex->FHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, parTex->FData);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_PRIORITY, 1.0); 

        glBindTexture(GL_TEXTURE_2D, 0);
    }

    void CreateDataTexture(TTexture* parTex)
    {
        RENDER_INFO("Creating data texture "<<parTex->FWidth<<"x"<<parTex->FHeight);

        glGenTextures(1, &(parTex->FID));
        glBindTexture(GL_TEXTURE_2D, parTex->FID);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, parTex->FWidth, parTex->FHeight, 0, GL_RGB, GL_FLOAT, parTex->FData);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glBindTexture(GL_TEXTURE_2D, 0);
    }

    void ReLoadTexture(TTexture* parTex)
    {
        glBindTexture(GL_TEXTURE_2D, parTex->FID);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, parTex->FWidth, parTex->FHeight, 0, GL_RGB, GL_FLOAT, parTex->FData);
        glBindTexture(GL_TEXTURE_2D, 0);
    }

    void TakeScreenShot(const std::string& parFileName)
    {
#if __posix__
        unsigned char *pdata = new unsigned char[1280*720*3];
        glReadPixels(0, 0, 1280, 720, GL_RGB, GL_UNSIGNED_BYTE, pdata);

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
	ASSERT_NOT_IMPLEMENTED()
#endif
    }

    void SaveTextureToFile(const std::string& parFileName, const TTexture* parTexture)
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
	ASSERT_NOT_IMPLEMENTED()
#endif
    }

}
}