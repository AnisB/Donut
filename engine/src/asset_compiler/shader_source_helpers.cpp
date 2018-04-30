// Internal includes
#include "asset_compiler/shader_source_helpers.h"

// Bento include
#include <bento_tools/file_system.h>

namespace donut
{
	bool read_shader_source(const char* target_path, TShaderSource& output_shader)
	{
		return bento::read_file(target_path, output_shader.data, bento::FileType::Text);
	}
}