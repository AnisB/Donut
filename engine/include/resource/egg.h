#pragma once

// Bento includes
#include <bento_memory/common.h>
#include <bento_collection/vector.h>
#include <bento_math/types.h>

namespace donut
{
	struct TEgg
	{
		TEgg(bento::IAllocator& allocator)
		: _vert_normal_uvs(allocator)
        , _indexes(allocator)
		{
		}

		bento::Vector<float> _vert_normal_uvs;
		bento::Vector<bento::IVector3> _indexes;
	};
}

namespace bento
{
	void pack_type(Vector<char>& buffer, const donut::TEgg& egg);
	bool unpack_type(const char*& stream, donut::TEgg& egg);
}