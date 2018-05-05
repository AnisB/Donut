// Bento includes
#include <asset_compiler/compiler.h>

int main(int argc, char** argv)
{
	// Allocator used for this program
	bento::IAllocator& current_alloc = *bento::common_allocator();

	// Collect the arguments
	bento::Vector<bento::DynamicString> arg_array(current_alloc);
	arg_array.resize(argc);
	for (uint32_t arg_idx = 0; arg_idx < argc; ++arg_idx)
	{
		arg_array[arg_idx] = argv[arg_idx];
	}

	// Build the compiler options
	donut::TCompilerOptions options(current_alloc);
	donut::asset_compiler::build_from_args(options, arg_array);

	// Compile
	donut::TAssetDatabase asset_db(*bento::common_allocator());
	bool result = donut::asset_compiler::compile(options, asset_db);
	
	// Write it to the disk
	donut::asset_compiler::write(options, asset_db);

	return 0;
}