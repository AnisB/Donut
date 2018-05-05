#pragma once

// Internal includes
#include "asset_compiler/asset_database_helpers.h"
#include "asset_compiler/compiler_options.h"

namespace donut {
namespace asset_compiler {

	bool compile(const TCompilerOptions& options, TAssetDatabase& asset_db);
	void write(const TCompilerOptions& options, const TAssetDatabase& asset_db);
}
}