#ifndef SUGAR_DESCRIPTOR_H
#define SUGAR_DESCRIPTOR_H

// Library includes
#include "graphics/material.h"
#include "identifier.h"

// External includes
#include <map>

namespace donut
{
	// Renderable descriptor
	struct TRenderableDescriptor
	{
		STRING_TYPE		id;
		STRING_TYPE		geometry;
		STRING_TYPE		material;
	};

	// Sugar descriptor
	struct TSugarDescriptor
    {
        STRING_TYPE    name;
        STRING_TYPE    file;

		std::map<STRING_TYPE, TRenderableDescriptor> renderables;
        
        // For tracking the file's state
        RECIPE_GUID id;
    };

	void ParseSugarFile(const STRING_TYPE& parFileName, TSugarDescriptor& _sugar);
    bool HasChanged(const TSugarDescriptor& _sugarDescriptor);
}

#endif // SUGAR_DESCRIPTOR_H