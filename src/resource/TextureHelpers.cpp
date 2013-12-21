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
#include <Base/DebugPrinters.h> 

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

        FILE* f = fopen(Filename, "rb");

        if(f==NULL)
        {
            INPUT_ERR("Erreur ouverture fichier "<<Filename);  
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
