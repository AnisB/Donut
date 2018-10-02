#pragma once

// Libary includes
#include "graphics/shaderdata.h"
#include "resource/topping_descriptor.h"

namespace donut
{
	namespace TPassTag
	{
		enum Type
		{
			GEOMETRY = 0,
			VFX = 1,
			UNKNOWN = -1
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

	struct TCanvasOutput
	{
		ALLOCATOR_BASED;
		TCanvasOutput(bento::IAllocator& alloc)
		: slot(alloc)
		{
		}
		TTextureNature::Type nature;
		bento::DynamicString slot;
	};

	// Descriptor for a rendering pipeline
    struct TPipelineCanvas
    {
		ALLOCATOR_BASED;
		TPipelineCanvas(bento::IAllocator& alloc)
		: outputs(alloc)
		{
		}
		bool depthTest;
		bento::Vector<TCanvasOutput> outputs;
    };

    struct TPipelineVFX
    {
		ALLOCATOR_BASED;
		TPipelineVFX(bento::IAllocator& alloc)
		: tag((uint8_t)TVFXTag::UNKNOWN)
		, shader_pipeline(alloc)
		, data(alloc)
		{

		}
		uint8_t tag;
		TShaderPipelineDescriptor shader_pipeline;
		bento::Vector<TShaderDataDescriptor> data;
    };

    struct TPipelinePass
    {
		ALLOCATOR_BASED;
		TPipelinePass(bento::IAllocator& alloc)
		: tag((uint8_t)TPassTag::UNKNOWN)
		, canvas(alloc)
		, vfx(alloc)
		, name(alloc)
		{
		}
		bento::DynamicString name;
		uint8_t tag;
        TPipelineCanvas  canvas;
        TPipelineVFX  vfx;
    };

    struct TPipelineDescriptor
    {
		ALLOCATOR_BASED;
		TPipelineDescriptor(bento::IAllocator& alloc)
		: name(alloc)
		, passes(alloc)
		{
		}
		bento::DynamicString name;
        bento::Vector<TPipelinePass> passes;
    };
}

namespace bento
{
    void pack_type(bento::Vector<char>& buffer, const donut::TPipelineDescriptor& pipeline);
    bool unpack_type(const char*& stream, donut::TPipelineDescriptor& pipeline);
}