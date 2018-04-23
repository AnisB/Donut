// Bento includes
#include <bento_base/log.h>

// Engine includes
#include <asset_compiler/compiler_options.h>

int main(int argc, char** argv)
{
	bento::default_logger()->log(bento::LogLevel::info, "ASSERT_COMPILER", "Starting the asset compiler");

	// Asset compiler allocator
	bento::IAllocator& current_allocator = *bento::common_allocator();

	// Put the args into a list
	bento::Vector<bento::DynamicString> arg_list(current_allocator);
	for(uint32_t arg_idx = 0; arg_idx < argc; ++arg_idx)
	{
		arg_list.push_back(bento::DynamicString(current_allocator, argv[arg_idx]));
	}

	// Build the compiler options from the args
	donut::TCompilerOptions compiler_option(current_allocator);
	bool valid_options = donut::asset_compiler::build_from_args(compiler_option, arg_list);

	// Check the validity of the options
	if(!valid_options)
	{
		bento::default_logger()->log(bento::LogLevel::info, "ASSERT_COMPILER", "Invalid compiler options");
		return -1;
	}

	return 0;
}