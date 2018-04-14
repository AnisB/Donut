#pragma once

// External includes
#include <string>

namespace donut
{
	// Foward declare
	struct TEgg;

	// Read an egg file
	TEgg* ReadEggFile(const std::string& _eggFileLocation);
}