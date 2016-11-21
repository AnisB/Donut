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



#ifndef TEXTURE
#define TEXTURE


#ifdef MACOSX
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#endif

#include <GLFW/glfw3.h>

#include <string>


namespace TImgType
{
	enum Type
	{
		JPG,
		PNG,
		BMP,
		TGA,
		NONE
	};
}

namespace TDataType
{
    enum Type
    {
        FLOAT,
        UNSIGNED_BYTE
    };
}

struct TTexture
{
	GLuint            FID;
    GLuint            FWidth;
    GLuint            FHeight;
    GLvoid *          FData;
    TDataType::Type   FDataType;

    std::string       FFileName;
    TImgType::Type    FType;
    GLuint            FFormat;
    unsigned          FNbRef;

    TTexture(std::string parFilename, TImgType::Type parType, int parWidth, int parHeight )
        : FWidth ( parWidth  )
        , FHeight( parHeight )
        , FData ( NULL )
        , FFileName ( parFilename )
        , FType (parType)
        , FNbRef(0)
        , FDataType(TDataType::UNSIGNED_BYTE)
        , FFormat(0)
    {
    }
    TTexture(int parWidth, int parHeight )
        : FWidth ( parWidth  )
        , FHeight( parHeight )
        , FData ( NULL )
        , FFileName ( "RUNTIME" )
        , FType (TImgType::NONE)
        , FNbRef(0)
        , FDataType(TDataType::UNSIGNED_BYTE)
        , FFormat(0)
    {
    }

    ~TTexture( void )
    {
        if( FData )
        {
            switch(FDataType)
            {
                case TDataType::UNSIGNED_BYTE:
                    delete [] (unsigned char*)FData;
                break;
                case TDataType::FLOAT:
                    delete [] (GLfloat*)FData;
                break;
            }
        }
    }
};

struct TSkyboxTexture
{
    GLuint             id;
    TTexture*          textures[6];
    std::string        filename;

    TSkyboxTexture(const std::string& _filename)
    : filename ( _filename )
    , id(0)
    , textures()
    {
    }

    ~TSkyboxTexture( void )
    {
    }
};

#endif // TEXTURE
 