#pragma once

// External includes
#include <stdint.h>

namespace donut
{
	namespace RenderingBackEnd
	{
		enum Type
		{
			OPENGL = 0,
			VULKAN = 1,
			COUNT = 2
		};
	}

	// Types definition
	typedef uint64_t RenderEnvironment;
	typedef uint64_t RenderWindow;
	typedef uint64_t GeometryObject;
	typedef uint64_t FramebufferObject;
	typedef uint64_t TextureObject;
	typedef uint64_t CubemapObject;
	typedef uint64_t ShaderPipelineObject;
}