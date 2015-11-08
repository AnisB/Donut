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

namespace Donut
{
    struct TBuildIn
    {
        TShaderData::Type dataType;
        std::string name;
    };

    struct TTextureInfo
    {
        int offset;
        std::string name;
        std::string file;
        GLuint texID;
        TTextureInfo()
        {
            offset=0;
            texID=0;
        }
        TTextureInfo(const TTextureInfo& parTextureInfo)
        {
            offset=parTextureInfo.offset;
            name=parTextureInfo.name;
            file=parTextureInfo.file;
            texID=parTextureInfo.texID;
        }
    };

    struct TCubeMapInfo
    {
        int offset;
        std::string name;
        std::string path;
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
 