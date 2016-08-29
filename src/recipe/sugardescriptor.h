#ifndef SUGAR_DESCRIPTOR_H
#define SUGAR_DESCRIPTOR_H

// Library includes
#include "base/common.h"
#include "graphics/material.h"
#include "identifier.h"

namespace Donut
{
	// Renderable descriptor
	struct TRenderableDescriptor
	{
		STRING_TYPE    geometry;
		STRING_TYPE    material;
	};

	// Sugar descriptor
	struct TSugarDescriptor
    {
        STRING_TYPE    name;
        STRING_TYPE    file;

		std::vector<TRenderableDescriptor> renderables;
        
        // For tracking the file's state
        RECIPE_GUID id;
    };

	void ParseSugarFile(const STRING_TYPE& parFileName, TSugarDescriptor& _sugar);
    bool HasChanged(const TSugarDescriptor& _sugarDescriptor);
}

#endif // SUGAR_DESCRIPTOR_H