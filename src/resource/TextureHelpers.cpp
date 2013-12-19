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


#include "TextureHelpers.h"

#include <stdio.h>
#include <stdlib.h>

 

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
    
    TTexture* LoadBMP(const char *Filename )
    {
        if( !Filename )
            return NULL;

        FILE *file;
        unsigned int  width;
        unsigned int  height;
        unsigned long i;
        unsigned short int planes; // planes in image (must be 1) 
        unsigned short int bpp;    // bits per pixel (must be 24)
    
        // make sure the file is there.
        if( ( file = fopen( Filename, "rb" ) ) == NULL )
        {
            printf( "File Not Found : %s\n", Filename );
            return NULL;
        }

        // seek through the bmp header, up to the width/height:
        fseek( file, 18, SEEK_CUR );

        // read the width
        if( ( i = ( unsigned long )fread( &width, 4, 1, file ) ) != 1 )
        {
            printf( "Error reading width from %s.\n", Filename );
            return NULL;
        }

        // read the height 
        if( ( i = ( unsigned long )fread( &height, 4, 1, file ) ) != 1 )
        {
            printf( "Error reading height from %s.\n", Filename );
            return NULL;
        }

        // read the planes
        if( ( ( unsigned long )fread( &planes, 2, 1, file ) ) != 1 )
        {
            printf( "Error reading planes from %s.\n", Filename );
            return NULL;
        }

        if( planes != 1 )
        {
            printf( "Planes from %s is not 1: %u\n", Filename, planes );
            return NULL;
        }

        // read the bpp
        if( ( i = ( unsigned long )fread( &bpp, 2, 1, file ) ) != 1 )
        {
            printf("Error reading bpp from %s.\n", Filename );
            return NULL;
        }

        if( bpp != 24 )
        {
            printf( "Bpp from %s is not 24: %u\n", Filename, bpp );
            return NULL;
        }

        // seek past the rest of the bitmap header.
        fseek( file, 24, SEEK_CUR );

        // read the data.
        TTexture* Image = new TTexture(Filename,TImgType::BMP, width, height );

        if( ( i = ( unsigned long )fread( Image->FData, width * height * 3, 1, file ) ) != 1 )
        {
            printf("Error reading image data from %s.\n", Filename );
            delete Image;
            return NULL;
        }
        return Image;
    }

 	TTexture * LoadTexture(const std::string & parImg)
 	{
 		TImgType::Type typeImg = GetImgType(parImg);

 		TTexture * texture = NULL;
	    switch (typeImg)
	    {
	    	case TImgType::PNG:
	    	    texture = NULL;
	    	    break;
	    	case TImgType::JPG:
	    	    texture = NULL;
	    	    break;
	    	case TImgType::BMP:
	    	    texture = LoadBMP(parImg.c_str());
	    	    break;
	    	case TImgType::TGA:
	    	    texture = NULL;
	    	    break;
    	    default:
    	        texture = NULL;
	    };
	    return texture;
	}






}
