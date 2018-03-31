#pragma once

// Library includes
#include "graphics/uniformhandler.h"

// STL includes
#include <string.h>
#include <vector>

namespace donut
{
    struct TBuildIn
    {
        TShaderData::Type dataType;
        STRING_TYPE name;
    };

    // Should be moved to texture when it will be refactored
    namespace TTextureNature 
    {
        enum Type
        {
            COLOR,
            DEPTH
        };
    };


	struct TBRDFInfo
	{
		int offset;
		STRING_TYPE name;
		STRING_TYPE file;
		uint32_t texID;
		TBRDFInfo()
		{
			offset = 0;
			texID = 0;
		}

		TBRDFInfo(const TBRDFInfo& _texture)
		{
			offset = _texture.offset;
			name = _texture.name;
			file = _texture.file;
			texID = _texture.texID;
		}
	};

    struct TTextureInfo
    {
        int offset;
        STRING_TYPE name;
        STRING_TYPE file;
        uint32_t texID;
        TTextureNature::Type type;
        TTextureInfo()
        {
            offset=0;
            texID=0;
        }
        TTextureInfo(const TTextureInfo& _texture)
        {
            offset = _texture.offset;
            name = _texture.name;
            file = _texture.file;
            texID = _texture.texID;
            type = _texture.type;
        }
    };

    struct TCubeMapInfo
    {
        int offset;
        STRING_TYPE name;
        STRING_TYPE path;
        uint32_t cmID;
        TCubeMapInfo()
        {
            offset=0;
            cmID=0;
        }
        TCubeMapInfo(const TCubeMapInfo& parCubeMapInfo)
        {
            offset=parCubeMapInfo.offset;
            name=parCubeMapInfo.name;
            path=parCubeMapInfo.path;
            cmID=parCubeMapInfo.cmID;
        }
    };
}