#ifndef SUGAR_DESCRIPTOR_H
#define SUGAR_DESCRIPTOR_H

// Library includes
#include "base/common.h"
#include "graphics/material.h"
#include "identifier.h"

namespace Donut
{
	// Sugar descriptor
	struct TSugarDescriptor
    {

        STRING_TYPE    name;
        STRING_TYPE    file;
		STRING_TYPE    geometry;
        TMaterial      material;
        
        // For tracking the file's state
        RECIPE_GUID id;
    };

	void ParseSugarFile(const STRING_TYPE& parFileName, TSugarDescriptor& _sugar);
    bool HasChanged(const TSugarDescriptor& _sugarDescriptor);
}

#endif // SUGAR_DESCRIPTOR_H