#pragma once

// Internal includes
#include "resource/asset_database.h"

namespace donut
{
	bool write_database(const char* target_path, const TAssetDatabase& target_database);
	bool read_database(const char* target_path, TAssetDatabase& output_database);
}