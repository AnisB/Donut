// Internal includes
#include "asset_compiler/asset_database_helpers.h"

// Bento includes
#include "bento_tools/disk_serializer.h"

// External includes
#include <json.hpp>

namespace donut
{
	const char* database_file_extension = "adb";
	const char* database_debug_file_extension = "json";

	bool write_database(const char* target_path, const TAssetDatabase& target_database)
	{
		// Get the file's directory and filename
		const bento::DynamicString& db_directory = bento::path::directory(target_path, *bento::common_allocator());
		const bento::DynamicString& filename = bento::path::filename(target_path, *bento::common_allocator());

		// Create the serializer
		bento::DiskSerializer serializer(*bento::common_allocator(), db_directory.c_str());

		// Write the file
		bool db_written = serializer.write_binary(target_database, filename.c_str(), database_file_extension);

		// return the result
		return db_written;
	}

	bool read_database(const char* target_path, TAssetDatabase& output_database)
	{
		// Get the file's directory and filename
		const bento::DynamicString& db_directory = bento::path::directory(target_path, *bento::common_allocator());
		const bento::DynamicString& filename = bento::path::filename(target_path, *bento::common_allocator());

		// Create the serializer
		bento::DiskSerializer serializer(*bento::common_allocator(), db_directory.c_str());

		// Read the file
		bool db_written = serializer.read_binary(output_database, filename.c_str(), database_file_extension);

		// return the result
		return db_written;
	}


	bool write_database_debug(const char* target_path, const TAssetDatabase& target_database)
	{
		const bento::DynamicString& db_directory = bento::path::directory(target_path, *bento::common_allocator());
		const bento::DynamicString& filename = bento::path::filename(target_path, *bento::common_allocator());

		bento::DiskSerializer serializer(*bento::common_allocator(), db_directory.c_str());

		// Write the file
		bool db_debug_written = serializer.write_string(target_database, filename.c_str(), database_debug_file_extension);

		// return the result
		return db_debug_written;
	}
}