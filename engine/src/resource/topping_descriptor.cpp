// Library include
#include "resource/topping_descriptor.h"

// Bento includes
#include <bento_base/stream.h>

namespace bento
{
	const uint32_t TOPPING_DESCRIPTOR_VERSION = 1;

	void pack_type(bento::Vector<char>& buffer, const donut::TShaderPipelineDescriptor& shader_pipeline)
	{
		pack_type(buffer, shader_pipeline.vertex);
		pack_type(buffer, shader_pipeline.tess_control);
		pack_type(buffer, shader_pipeline.tess_eval);
		pack_type(buffer, shader_pipeline.geometry);
		pack_type(buffer, shader_pipeline.fragment);
	}

	void unpack_type(const char*& stream, donut::TShaderPipelineDescriptor& shader_pipeline)
	{
		unpack_type(stream, shader_pipeline.vertex);
		unpack_type(stream, shader_pipeline.tess_control);
		unpack_type(stream, shader_pipeline.tess_eval);
		unpack_type(stream, shader_pipeline.geometry);
		unpack_type(stream, shader_pipeline.fragment);
	}

	void pack_type(bento::Vector<char>& buffer, const donut::TShaderDataDescriptor& shader_data)
	{
		pack_bytes(buffer, shader_data.type);
		pack_type(buffer, shader_data.slot);
		pack_type(buffer, shader_data.data);
	}

	void unpack_type(const char*& stream, donut::TShaderDataDescriptor& shader_data)
	{
		unpack_bytes(stream, shader_data.type);
		unpack_type(stream, shader_data.slot);
		unpack_type(stream, shader_data.data);
	}

	void pack_type(bento::Vector<char>& buffer, const donut::TToppingDescriptor& topping)
	{
		pack_bytes(buffer, TOPPING_DESCRIPTOR_VERSION);
		pack_type(buffer, topping.name);
		pack_type(buffer, topping.shader_pipeline);
		pack_vector_types(buffer, topping.data);
	}

	bool unpack_type(const char*& stream, donut::TToppingDescriptor& topping)
	{
		// Read the version
		uint32_t data_stream_version;
		bento::unpack_bytes(stream, data_stream_version);

		// Stop if this does not match the current version
		if (data_stream_version != TOPPING_DESCRIPTOR_VERSION) return false;

		unpack_type(stream, topping.name);
		unpack_type(stream, topping.shader_pipeline);
		unpack_vector_types(stream, topping.data);
		return true;
	}
}