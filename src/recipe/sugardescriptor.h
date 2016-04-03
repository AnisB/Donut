#ifndef SUGAR_DESCRIPTOR_H
#define SUGAR_DESCRIPTOR_H

// Library includes
#include "base/common.h"
#include "graphics/material.h"
#include "identifier.h"

namespace Donut
{
	struct TSugarDescriptor
    {
        std::string     name;
        std::string     geometry;
        TMaterial       material;
        
        // For tracking the file's state
        RECIPE_GUID id;

        TSugarDescriptor( )
        {
        }

        TSugarDescriptor(const TSugarDescriptor& _sugar)
        {
            name = _sugar.name;
            geometry = _sugar.geometry;
            material = _sugar.material;
            id = _sugar.id;
        }
    };

	void ParseSugarFile(const std::string& parFileName, TSugarDescriptor& _sugar);
}

#endif // SUGAR_DESCRIPTOR_H