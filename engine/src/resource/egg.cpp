// Bento includes
#include <bento_base/stream.h>

// Library includes
#include "resource/egg.h"

using namespace donut;

// Current version of the egg format
const uint32_t EGG_DATA_VERSION = 0;

namespace bento
{
	void pack_type(Vector<char>& buffer, const TEgg& egg)
	{
		pack_bytes(buffer, EGG_DATA_VERSION);
		pack_vector_bytes(buffer, egg._vert_normal_uvs);
		pack_vector_bytes(buffer, egg._indexes);
	}

	bool unpack_type(const char*& stream, TEgg& egg)
	{
		// Read the version
		uint32_t data_stream_version;
		unpack_bytes(stream, data_stream_version);

		// Stop if this does not match the current version
		if (data_stream_version != EGG_DATA_VERSION) return false;
		unpack_vector_bytes(stream, egg._vert_normal_uvs);
		unpack_vector_bytes(stream, egg._indexes);
		return true;
	}
}
