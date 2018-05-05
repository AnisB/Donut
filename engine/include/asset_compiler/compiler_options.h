#pragma once

// Bento includes
#include <bento_collection/dynamic_string.h>
#include <bento_collection/vector.h>

namespace donut
{
	struct TCompilerOptions
	{
		TCompilerOptions(bento::IAllocator& allocator)
		: _source_dir(allocator)
		, _output_dir(allocator)
		, _target_flour(allocator)
		{
		}

		bento::DynamicString _source_dir;
		bento::DynamicString _output_dir;
		bento::DynamicString _target_flour;
	};

	namespace asset_compiler
	{
		void build_from_args(TCompilerOptions& compiler_options, const bento::Vector<bento::DynamicString>& args);
	}
}