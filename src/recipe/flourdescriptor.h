#ifndef FLOUR_DESCRIPTOR_H
#define FLOUR_DESCRIPTOR_H

// Library includes
#include "base/common.h"
#include "identifier.h"

namespace Donut
{
	// The descriptor
	struct TFlourDescriptor
	{
		std::string name;
		std::string file;

        // For tracking the file's state
        RECIPE_GUID id;
	};

	void ParseFlourFile(const std::string& _fileName, TFlourDescriptor& _output);
}

#endif // FLOUR_DESCRIPTOR_H