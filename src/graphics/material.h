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

#ifndef MATERIAL_GRAPHICS_DONUT
#define MATERIAL_GRAPHICS_DONUT

// Library includes
#include "graphics/shaderdata.h"
#include "graphics/shader.h"
// STL inlcudes
#include <string>
#include <vector>

namespace Donut
{
    struct TMaterial
    {
        TMaterial()
        {
        }

        TMaterial(const TMaterial& _mat)
        {
            builtIns = _mat.builtIns;
            uniforms = _mat.uniforms;
            textures = _mat.textures;
            cubeMaps = _mat.cubeMaps;
            shader = _mat.shader;
        }

        // Attributes
        TShader                         shader;
        std::vector<TBuildIn>           builtIns;
        std::vector<TUniformHandler>    uniforms;
        std::vector<TTextureInfo>       textures;
        std::vector<TCubeMapInfo>       cubeMaps;
    };
}

#endif // MATERIAL_GRAPHICS_DONUT
 