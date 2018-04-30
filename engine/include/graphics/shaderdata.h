#pragma once

// Internal includes
#include <gpu_backend/gpu_backend.h>

// STL includes
#include <string.h>
#include <vector>

namespace donut
{
	enum class TShaderDataType
	{
		INTEGER = 0,
		FLOAT = 1,
		VEC3 = 2,
		VEC4 = 3,
		MAT3 = 4,
		MAT4 = 5,
		TEXTURE2D = 6,
		CUBEMAP = 7,
		TYPE = 8
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

	struct TTextureInfo
    {
        TextureObject id;
		std::string name;
		int offset;
		TTextureNature::Type type;

        TTextureInfo()
        {
            offset = 0;
			id = 0;
        }
    };

    struct TCubeMapInfo
    {
		std::string name;
        CubemapObject id;
		int offset;

		TCubeMapInfo()
        {
            offset = 0;
			id = 0;
        }
    };
}