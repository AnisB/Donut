#pragma once

// Library includes
#include "graphics/uniformhandler.h"
#include "gpu_backend/gpu_backend.h"

// STL inlcudes
#include <string>
#include <vector>

namespace donut
{
    struct TMaterial
    {
        ShaderPipelineObject            shader;
        std::vector<TUniform>			uniforms;
		std::vector<TTextureInfo>       textures;
        std::vector<TCubeMapInfo>       cubeMaps;
        uint8_t                         flags;
    };


    void inject_material(ShaderPipelineObject program, const TMaterial& material, const GPUBackendAPI* backendAPI);
}