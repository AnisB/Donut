// Bento includes
#include <bento_base/log.h>

// Internal includes
#include "asset_compiler/compiler_options.h"

namespace donut {
namespace asset_compiler {

	bool build_from_args(TCompilerOptions& compiler_options, const bento::Vector<bento::DynamicString>& args)
	{
		bool valid_input = false;
		bool valid_output = false;
		uint32_t current_arg_idx = 0;
		const uint32_t num_args = args.size();
		while(current_arg_idx < num_args)
		{
			if(args[current_arg_idx] == "--source-dir")
			{
				if(current_arg_idx == num_args - 1)
				{
					bento::default_logger()->log(bento::LogLevel::error, "ASSET_COMPILER", "please provide a source directory");
					continue;
				}
				compiler_options._source_dir = args[current_arg_idx + 1];
				current_arg_idx += 2;
				valid_input = true;
			}
			else if(args[current_arg_idx] == "--output-dir")
			{
				if(current_arg_idx == num_args - 1)
				{
					bento::default_logger()->log(bento::LogLevel::error, "ASSET_COMPILER", "please provide an output directory");
					continue;
				}
				compiler_options._output_dir = args[current_arg_idx + 1];
				current_arg_idx += 2;
				valid_output = true;
			}
			else
			{
				bento::default_logger()->log(bento::LogLevel::error, "ASSET_COMPILER", "unrecognized compiler option");
				current_arg_idx++;
			}
		}

		return valid_input && valid_output;
	}
}
}