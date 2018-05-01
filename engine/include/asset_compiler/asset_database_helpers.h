#pragma once

// Internal includes
#include "resource/asset_database.h"

namespace donut
{
	// Helpers to write the binary version of the database
	bool write_database(const char* target_path, const TAssetDatabase& target_database);
	bool read_database(const char* target_path, TAssetDatabase& output_database);

	// Helpers to write the debug info of the database
	bool write_database_debug(const char* target_path, const TAssetDatabase& target_database);
}