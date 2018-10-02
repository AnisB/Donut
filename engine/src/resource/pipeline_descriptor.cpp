// Bento includes
#include "resource/pipeline_descriptor.h"
#include <bento_base/stream.h>

namespace bento
{
	const uint32_t PIPELINE_DATA_VERSION = 2;

	void pack_type(bento::Vector<char>& buffer, const donut::TPipelineVFX& pipeline_vfx)
	{
		pack_bytes(buffer, pipeline_vfx.tag);
		pack_type(buffer, pipeline_vfx.shader_pipeline);
		pack_vector_types(buffer, pipeline_vfx.data);
	}

	void unpack_type(const char*& stream, donut::TPipelineVFX& pipeline_vfx)
	{
		unpack_bytes(stream, pipeline_vfx.tag);
		unpack_type(stream, pipeline_vfx.shader_pipeline);
		unpack_vector_types(stream, pipeline_vfx.data);
	}

	void pack_type(bento::Vector<char>& buffer, const donut::TCanvasOutput& canvasOutput)
	{
		pack_type(buffer, canvasOutput.slot);
		pack_bytes(buffer, canvasOutput.nature);
	}

	void unpack_type(const char*& stream, donut::TCanvasOutput& canvasOutput)
	{
		unpack_type(stream, canvasOutput.slot);
		unpack_bytes(stream, canvasOutput.nature);
	}

	void pack_type(bento::Vector<char>& buffer, const donut::TPipelineCanvas& pipeline_canvas)
	{
		pack_bytes(buffer, pipeline_canvas.depthTest);
		pack_vector_types(buffer, pipeline_canvas.outputs);
	}

	void unpack_type(const char*& stream, donut::TPipelineCanvas& pipeline_canvas)
	{
		unpack_bytes(stream, pipeline_canvas.depthTest);
		unpack_vector_types(stream, pipeline_canvas.outputs);
	}

	void pack_type(bento::Vector<char>& buffer, const donut::TPipelinePass& pipeline_pass)
	{
		pack_type(buffer, pipeline_pass.name);
		pack_bytes(buffer, pipeline_pass.tag);
		pack_type(buffer, pipeline_pass.canvas);
		pack_type(buffer, pipeline_pass.vfx);
	}

	void unpack_type(const char*& stream, donut::TPipelinePass& pipeline_pass)
	{
		unpack_type(stream, pipeline_pass.name);
		unpack_bytes(stream, pipeline_pass.tag);
		unpack_type(stream, pipeline_pass.canvas);
		unpack_type(stream, pipeline_pass.vfx);
	}


    void pack_type(bento::Vector<char>& buffer, const donut::TPipelineDescriptor& pipeline)
	{
		pack_bytes(buffer, PIPELINE_DATA_VERSION);
		pack_type(buffer, pipeline.name);
		pack_vector_types(buffer, pipeline.passes);
	}

    bool unpack_type(const char*& stream, donut::TPipelineDescriptor& pipeline)
	{
		// Read the version
		uint32_t data_stream_version;
		unpack_bytes(stream, data_stream_version);

		// Stop if this does not match the current version
		if (data_stream_version != PIPELINE_DATA_VERSION) return false;

		unpack_type(stream, pipeline.name);
		unpack_vector_types(stream, pipeline.passes);
		return true;
	}
}