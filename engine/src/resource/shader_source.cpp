// Internal includes
#include "resource/shader_source.h"

// Bento includes
#include <bento_base/stream.h>
namespace bento
{
	const uint32_t SHADER_SOURCE_VERSION =  1;

	void pack_type(bento::Vector<char>& buffer, const donut::TShaderSource& shader_source)
	{
		bento::pack_bytes(buffer, SHADER_SOURCE_VERSION);
		bento::pack_vector_bytes(buffer, shader_source.data);
	}

	bool unpack_type(const char*& stream, donut::TShaderSource& shader_source)
	{
		// Read the version
		uint32_t data_stream_version;
		bento::unpack_bytes(stream, data_stream_version);

		// Stop if this does not match the current version
		if (data_stream_version != bento::SHADER_SOURCE_VERSION) return false;
		bento::unpack_vector_bytes(stream, shader_source.data);
		return true;
	}
}