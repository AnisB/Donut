#pragma once

// Library includes
#include "resource/types.h"
#include "graphics/uniformhandler.h"

// Bento includes
#include <bento_math/types.h>

// External includes
#include <map>

namespace donut
{
	namespace RenderFlags
	{
		enum Type
		{
			NONE = 0,
			NO_CULLING = 1
		};
	}

	// This structure encapsulates everything that is required to draw a geometry with a material in a given scene
	struct TRenderRequest
	{
		// Instance data
		MATERIAL_GUID material;
		GEOMETRY_GUID geometry;

		// Set of flags that need to be applied to this request
		uint8_t render_flags;

		// Mesh transform
		bento::Matrix4 transform;
	};

	// Processed a render request (draw it to the screen)
	void ProcessRenderRequest(const TRenderRequest& _request, std::map<std::string, TUniform>& _uniforms);
}