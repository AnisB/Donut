#pragma once

// Library includes
#include "graphics/shaderdata.h"
#include "graphics/shader.h"
// STL inlcudes
#include <string>
#include <vector>

namespace donut
{
    struct TMaterial
    {
        TShader                         shader;
        std::vector<TBuildIn>           builtIns;
        std::vector<TUniformHandler>    uniforms;
		std::vector<TTextureInfo>       textures;
		std::vector<TBRDFInfo>			brfds;
        std::vector<TCubeMapInfo>       cubeMaps;
        uint8_t                         flags;
    };
}