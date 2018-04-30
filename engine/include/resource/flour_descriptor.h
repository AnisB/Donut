#pragma once

// Bento includes
#include <bento_math/types.h>
#include <bento_collection/vector.h>
#include <bento_collection/dynamic_string.h>

namespace donut
{
	struct TSHDescriptor
	{
		float red[9];
		float green[9];
		float blue[9];
		bool active;
	};

	struct TLightDescriptor
	{
		bento::Vector3  pos;
		bento::Vector4  diff;
		bento::Vector4  spec;
		float 			ray;
	};
	
	struct TNodeDescriptor
	{
		ALLOCATOR_BASED;
		TNodeDescriptor(bento::IAllocator& alloc)
		: tm()
        , children(alloc)
		, models(alloc)
		{
		}

		bento::Matrix4 						tm;
		bento::Vector<uint32_t> 			children;
		bento::Vector<bento::DynamicString> models;
	};

	struct TFlourDescriptor
	{
		ALLOCATOR_BASED;
		TFlourDescriptor(bento::IAllocator& alloc)
		: name(alloc)
		, pipeline(alloc)
		, skybox(alloc)
		, nodes(alloc)
		, lights(alloc)
		{
		}

		bento::DynamicString 			name;
		bento::DynamicString 			pipeline;
		bento::DynamicString 			skybox;
		TSHDescriptor					sh;
		bento::Vector<TNodeDescriptor>  nodes;
		bento::Vector<TLightDescriptor> lights;
	};
}

namespace bento
{
	void pack_type(bento::Vector<char>& buffer, const donut::TFlourDescriptor& flour);
	bool unpack_type(const char*& stream, donut::TFlourDescriptor& flour);
}