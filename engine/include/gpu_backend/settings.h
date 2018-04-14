#pragma once

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
		uint64_t data[5];
	};
}