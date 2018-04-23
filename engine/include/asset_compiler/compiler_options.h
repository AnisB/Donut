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
		{
		}

		bento::DynamicString _source_dir;
		bento::DynamicString _output_dir;
	};

	namespace asset_compiler
	{
		bool build_from_args(TCompilerOptions& compiler_options, const bento::Vector<bento::DynamicString>& args);
	}
}