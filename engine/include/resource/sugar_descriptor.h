#pragma once

// Bento includes
#include <bento_collection/dynamic_string.h>
#include <bento_collection/vector.h>

namespace donut
{
	struct TRenderableDescriptor
	{
    	ALLOCATOR_BASED;
		TRenderableDescriptor(bento::IAllocator& alloc)
		: id(alloc)
		, geometry(alloc)
		, material(alloc)
		{
		}

		bento::DynamicString  id;
		bento::DynamicString  geometry;
		bento::DynamicString  material;
	};

	struct TSugarDescriptor
    {
    	ALLOCATOR_BASED;
		TSugarDescriptor(bento::IAllocator& alloc)
		: _renderables(alloc)
		, _name(alloc)
		{
		}
		bento::DynamicString _name;
		bento::Vector<TRenderableDescriptor> _renderables;
    };
}

namespace bento
{
	void pack_type(bento::Vector<char>& buffer, const donut::TRenderableDescriptor& sugar);
	void unpack_type(const char*& stream, donut::TRenderableDescriptor& sugar);

	void pack_type(bento::Vector<char>& buffer, const donut::TSugarDescriptor& sugar);
	bool unpack_type(const char*& stream, donut::TSugarDescriptor& sugar);
}