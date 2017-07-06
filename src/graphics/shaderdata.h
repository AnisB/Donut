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

#ifndef SHADER_DATA_GRAPHICS_DONUT
#define SHADER_DATA_GRAPHICS_DONUT

// Library includes
#include "graphics/common.h"
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
		GLuint texID;
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
        GLuint texID;
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
        GLuint cmID;
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


#endif // SHADER_DATA_GRAPHICS_DONUT
 