// Bento include
#include <bento_base/stream.h>

// Internal includes
#include "resource/flour_descriptor.h"

namespace bento
{
	const uint32_t FLOOR_DATA_VERSION = 1;

	void pack_type(bento::Vector<char>& buffer, const donut::TNodeDescriptor& node)
	{
		pack_bytes(buffer, node.tm);
		pack_vector_bytes(buffer, node.children);
		pack_vector_types(buffer, node.models);
	}

	void unpack_type(const char*& stream, donut::TNodeDescriptor& node)
	{
		unpack_bytes(stream, node.tm);
		unpack_vector_bytes(stream, node.children);
		unpack_vector_types(stream, node.models);
	}

	void pack_type(bento::Vector<char>& buffer, const donut::TFlourDescriptor& flour)
	{
		pack_bytes(buffer, FLOOR_DATA_VERSION);
		pack_type(buffer, flour.name);
		pack_type(buffer, flour.pipeline);
		pack_type(buffer, flour.skybox);
		pack_bytes(buffer, flour.sh);
		pack_vector_types(buffer, flour.nodes);
		pack_vector_bytes(buffer, flour.lights);
	}

	bool unpack_type(const char*& stream, donut::TFlourDescriptor& flour)
	{
		// Read the version
		uint32_t data_stream_version;
		bento::unpack_bytes(stream, data_stream_version);

		// Stop if this does not match the current version
		if (data_stream_version != FLOOR_DATA_VERSION) return false;
		unpack_type(stream, flour.name);
		unpack_type(stream, flour.pipeline);
		unpack_type(stream, flour.skybox);
		unpack_bytes(stream, flour.sh);
		unpack_vector_types(stream, flour.nodes);
		unpack_vector_bytes(stream, flour.lights);
		return true;
	}
}