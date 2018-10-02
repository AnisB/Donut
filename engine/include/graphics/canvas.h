#pragma once

// Library includes
#include "gpu_backend/gpu_backend.h"
#include "graphics/shaderdata.h"
#include "graphics/material.h"
#include "resource/texture.h"

// External includes
#include <vector>

namespace donut
{
	// This structure holds the set of buffers that a given canvas can produce
	struct TBufferOutput
	{
		int width;
		int height;
		bool depthTest;
		std::vector<TTextureInfo> buffers;
	};

	class TCanvas
	{
	public:
		// Cst & Dst
		TCanvas(const GPUBackendAPI* gpuBackend);
		virtual ~TCanvas();

		// Setup the canvas
		virtual void setup(const TBufferOutput& bufferOutputData);

		virtual void init();
		virtual void enable();
		virtual void disable();

		const TBufferOutput& result();
	protected:
		// Pointer to the native API
		const GPUBackendAPI* _gpuBackend;

		// Flag that defines if we render in a custom frame buffer
		bool _customFrameBuffer;

		// Additional data for the binding
		uint32_t _numColorBuffers;

		// The ouput data of the canvas
		TBufferOutput _output;

		// Target frame buffer
		FramebufferObject _frameBuffer;
	};
}