#ifndef GEOMETRY_CONVERTERS_H
#define GEOMETRY_CONVERTERS_H

// Library includes
#include "base\Common.h"

namespace Donut
{
	// Foward declare
	struct TEgg;

	void ConvertWavefrontToEgg(const STRING_TYPE& _wavefront, const STRING_TYPE& _outputEggFile);
	void ExportEggFile(TEgg* eggInstance, const STRING_TYPE& _outputEggFile);
}

#endif // GEOMETRY_CONVERTERS_H