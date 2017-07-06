#ifndef PIPELINE_DESCRIPTOR_H
#define PIPELINE_DESCRIPTOR_H

// Libary includes
#include "graphics/shaderdata.h"
#include "identifier.h"

// External includes
#include <vector>

namespace donut
{
	namespace TCanvasTag
    {
        enum Type
        {
            UNKNOWN = 0,
            EMPTY = 1,
            EFFECT = 2,
            GBUFFER = 3,
        };
    }

    namespace TVFXTag
    {
        enum Type
        {
            UNKNOWN = 0,
            SIMPLEFX = 1,
            ENVIRONEMENT = 2,
            DEFFERED = 3,
            SKYBOX = 4,
        };
    }

    namespace TPassTag
    {
        enum Type
        {
            GEOMETRY = 0,
            VFX = 1,
            UNKNOWN = -1
        };
    }

    // Descriptor for a rendering pipeline
    struct TPipelineCanvas
    {
        TCanvasTag::Type tag;
        STRING_TYPE output;
    };

    struct TPipelineVFX
    {
        TVFXTag::Type tag;
        std::vector<TTextureInfo> textures;
        TShader shader;
    };

    struct TPipelinePass
    {
        TPassTag::Type tag;
        TPipelineCanvas  canvas;
        TPipelineVFX  vfx;
    };

	// The pipeline descriptor
    struct TPipelineDescriptor
    {
        std::vector<TPipelinePass> passes;
        STRING_TYPE name;
        STRING_TYPE file;
        // For tracking the file's state
        RECIPE_GUID id;
    };

    // Generate a pipeline descriptor from a file
    void ParsePipelineFile(const STRING_TYPE& _pipelineFileName, TPipelineDescriptor& _pipeline);
    bool HasChanged(const TPipelineDescriptor& _pipelineDescriptor);

}

#endif // PIPELINE_DESCRIPTOR_H