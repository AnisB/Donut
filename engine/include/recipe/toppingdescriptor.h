#ifndef TOPPING_DESCRIPTOR_H
#define TOPPING_DESCRIPTOR_H

// Library includes
#include "graphics/material.h"
#include "identifier.h"

// External includes
#include <vector>

namespace donut
{
	// Flour descriptor
	struct TToppingDescriptor
	{
		TToppingDescriptor()
		: loaded(false)
		{

		}
		// Generic data
        STRING_TYPE    name;
        STRING_TYPE    file;

        // Rendering data
        TMaterial data;
        bool loaded;

        // For tracking the file's state
        RECIPE_GUID id;
	};

	// Build a descriptor from a file 
	void ParseToppingFile(const STRING_TYPE& _fileName, TToppingDescriptor& _output);
    bool HasChanged(const TToppingDescriptor& _toppingDescriptor);
}

#endif // TOPPING_DESCRIPTOR_H