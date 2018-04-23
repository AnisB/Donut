// Library includes
#include "asset_compiler/egg_helpers.h"
#include "resource/egg.h"

// Bento includes
#include <bento_tools/disk_serializer.h>
#include <bento_tools/file_system.h>

namespace donut
{
	// Extension used for this file
	const char* egg_file_extension = "egg";

	bool write_egg(const char* egg_path, const TEgg& source_egg)
	{
		// Get the file's directory and filename
		const bento::DynamicString& egg_directory = bento::path::directory(egg_path, *bento::common_allocator());
		const bento::DynamicString& filename = bento::path::filename(egg_path, *bento::common_allocator());

		// Create the serializer
		bento::DiskSerializer serializer(*bento::common_allocator(), egg_directory.c_str());

		// Write the file
		bool egg_file_written = serializer.write_binary(source_egg, filename.c_str(), egg_file_extension);

		// return the result
		return egg_file_written;
	}

	bool read_egg(const char* egg_path, TEgg& output_egg)
	{
		// Get the file's directory and filename
		const bento::DynamicString& egg_directory = bento::path::directory(egg_path, *bento::common_allocator());
		const bento::DynamicString& filename = bento::path::filename(egg_path, *bento::common_allocator());

		// Create the serializer
		bento::DiskSerializer serializer(*bento::common_allocator(), egg_directory.c_str());

		// Read the file
		bool egg_file_read = serializer.read_binary(output_egg, filename.c_str(), egg_file_extension);

		// return the result
		return egg_file_read;
	}
}