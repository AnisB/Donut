// Library includes
#include "graphics/canvas.h"
#include "graphics/shaderdata.h"
#include "resource/resource_manager.h"

namespace donut
{
	// Init and delete
	TCanvas::TCanvas(const GPUBackendAPI* gpuBackend)
	: _gpuBackend(gpuBackend)
	, _numColorBuffers(0)
	, _customFrameBuffer(false)
	{
	}

	TCanvas::~TCanvas()
	{
	}

	void TCanvas::setup(const TBufferOutput& bufferOutputData)
	{
		// Copy the descriptor
		_output = bufferOutputData;
		// Reset the number color buffers
		_numColorBuffers = 0;
		// Reset the flag
		_customFrameBuffer = false;
	}

	void TCanvas::init()
	{
		// Is there any output buffer? if no, then we render in the default frame buffer
		if (_output.buffers.size())
		{
			// This canvas uses a custom frame buffer
			_customFrameBuffer = true;

			// Creating the main frame buffer
			_frameBuffer = _gpuBackend->frame_buffer_api.create();
			_gpuBackend->frame_buffer_api.bind(_frameBuffer);

			// The total number of buffers
			uint32_t numRenderTextures = (uint32_t)_output.buffers.size();

			for (uint32_t rtIdx = 0; rtIdx < numRenderTextures; ++rtIdx)
			{
				// Grab the current Buffer to instanciate
				TTextureInfo& textureInfo = _output.buffers[rtIdx];

				// Set its offset
				textureInfo.offset = rtIdx;

				// Create the descriptor
				TTexture texture(*bento::common_allocator());
				texture.width = _output.width;
				texture.height = _output.height;
				texture.format = textureInfo.type == TTextureNature::COLOR ? texture::TFormat::RGBA : texture::TFormat::DEPTH;
				texture.data_type = texture::TDataType::FLOAT;
				// Instanciate and keep track of the texture's id
				textureInfo.id = ResourceManager::Instance().create_runtime_texture(textureInfo.name.c_str(), texture);
				_gpuBackend->texture2D_api.set_debug_name(textureInfo.id, textureInfo.name.c_str());

				// Bind this texture to the frame buffer
				_gpuBackend->frame_buffer_api.bind_texture(_frameBuffer, textureInfo);

				// Count the number of color buffers
				_numColorBuffers += textureInfo.type == TTextureNature::COLOR ? 1 : 0;
			}

			// Making sure everything is OK
			_gpuBackend->frame_buffer_api.check(_frameBuffer);
			_gpuBackend->frame_buffer_api.unbind(_frameBuffer);
		}
	}

	void TCanvas::enable()
	{
		FramebufferObject targetFrameBuffer = _customFrameBuffer ? _frameBuffer : 0;
		uint32_t targetNumBuffers = _customFrameBuffer ? _numColorBuffers : 1;

		_gpuBackend->frame_buffer_api.bind(targetFrameBuffer);
		_gpuBackend->frame_buffer_api.enable_depth_test(targetFrameBuffer);
		_gpuBackend->frame_buffer_api.clear(targetFrameBuffer);

		if(_customFrameBuffer)
			_gpuBackend->frame_buffer_api.set_num_render_targets(targetFrameBuffer, targetNumBuffers);

		if (_output.depthTest)
			_gpuBackend->frame_buffer_api.enable_depth_test(targetFrameBuffer);
		else
			_gpuBackend->frame_buffer_api.disable_depth_test(targetFrameBuffer);

	}

	void TCanvas::disable()
	{
		FramebufferObject targetFrameBuffer = _customFrameBuffer ? _frameBuffer : 0;
		_gpuBackend->frame_buffer_api.unbind(targetFrameBuffer);
	}

	const TBufferOutput& TCanvas::result()
	{
		return _output;
	}
}