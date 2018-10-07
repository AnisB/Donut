#pragma once

// Internal includes
#include "resource/texture.h"

// External includes
#include <vector>

namespace donut
{
	// This structure holds the set of buffers that a given canvas can produce
	struct TFrameBufferOutput
	{
		int width;
		int height;
		bool depthTest;
		std::vector<TTextureInfo> buffers;
	};
}	
