#pragma once

// Internal include
#include "gpu_types.h"

// External includes
#include <stdint.h>
#include <string>
	
namespace donut
{
	struct TGraphicSettings
	{
		std::string window_name;
		uint32_t width;
		uint32_t lenght;
		bool fullscreen;
		RenderingBackEnd::Type backend;
		uint64_t data[5];
	};
}