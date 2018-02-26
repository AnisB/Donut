#ifndef SUGAR_DESCRIPTOR_H
#define SUGAR_DESCRIPTOR_H

// Library includes
#include "containers/vector.h"
#include "graphics/material.h"
#include "identifier.h"

// External includes
#include <map>

namespace donut
{
	// Renderable descriptor
	struct TRenderableDescriptor
	{
		// Identifier of the renderable
		STRING_TYPE		_id;
		// Name of the geometry used for this renderable
		STRING_TYPE		_geometry;
		// Name of the material used for this renderable
		STRING_TYPE		_material;
	};

	// Sugar descriptor
	struct TSugarDescriptor
    {
	private:
		TSugarDescriptor(const TSugarDescriptor&);
	public:
    	// Required stuff for allocation
    	ALLOCATOR_BASED;
		TSugarDescriptor(TAllocator* allocator = common_allocator()) : _renderables(*allocator) {}

    	// Name of the sugar
        STRING_TYPE _name;

        // FIle that the sugar was read from
        STRING_TYPE _file;

        // The set of renderables for this sugar
		TVector<TRenderableDescriptor> _renderables;
        
        // Identifier that tracks the state of the file
        RECIPE_GUID _id;
    };

    // Fill a sugar descriptor from a file
	void ParseSugarFile(const STRING_TYPE& parFileName, TSugarDescriptor& _sugar);

	// Check if the identification of a sugar is still coherent with the file
    bool HasChanged(const TSugarDescriptor& _sugarDescriptor);
}

#endif // SUGAR_DESCRIPTOR_H