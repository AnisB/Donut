#pragma once

// Bento includes
#include <bento_collection/dynamic_string.h>

namespace donut
{
	struct TShaderSource
	{
		TShaderSource(bento::IAllocator& alloc)
		: data(alloc)
		{
		}
		bento::Vector<char> data;
	};
}

namespace bento
{
	void pack_type(bento::Vector<char>& buffer, const donut::TShaderSource& shader_source);
	bool unpack_type(const char*& stream, donut::TShaderSource& shader_source);
}
