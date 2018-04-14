#pragma once


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
	uint32_t          FID;
	uint32_t          FWidth;
	uint32_t          FHeight;
    unsigned char *   FData;
    TDataType::Type   FDataType;

    STRING_TYPE       FFileName;
    TImgType::Type    FType;
	uint32_t          FFormat;
    unsigned          FNbRef;

    TTexture(STRING_TYPE parFilename, TImgType::Type parType, int parWidth, int parHeight )
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
                    delete [] (float*)FData;
                break;
            }
        }
    }
};

struct TSkyboxTexture
{
    uint32_t             id;
    TTexture*          textures[6];
    STRING_TYPE        filename;

    TSkyboxTexture(const STRING_TYPE& _filename)
    : filename ( _filename )
    , id(0)
    , textures()
    {
    }

    ~TSkyboxTexture( void )
    {
    }
}; 