#ifndef EGG_HELPERS_H
#define EGG_HELPERS_H

// Library includes
#include "common.h"

namespace Donut
{
	// Foward declare
	struct TEgg;

	// Read an egg file
	TEgg* ReadEggFile(const STRING_TYPE& _eggFileLocation);
}

#endif // EGG_HELPERS_H