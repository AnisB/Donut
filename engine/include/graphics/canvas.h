#pragma once

// Library includes
#include "gpu_backend/gpu_backend.h"
#include "graphics/shaderdata.h"
#include "graphics/material.h"
#include "graphics/frame_buffer_output.h"

namespace donut
{
	class TCanvas
	{
	public:
		// Cst & Dst
		TCanvas(const GPUBackendAPI* gpuBackend);
		virtual ~TCanvas();

		// Setup the canvas
		virtual void setup(const TFrameBufferOutput& bufferOutputData);

		virtual void init();
		virtual void enable();
		virtual void disable();

		const TFrameBufferOutput& result();
	protected:
		// Pointer to the native API
		const GPUBackendAPI* _gpuBackend;

		// Flag that defines if we render in a custom frame buffer
		bool _customFrameBuffer;

		// Additional data for the binding
		uint32_t _numColorBuffers;

		// The ouput data of the canvas
		TFrameBufferOutput _output;

		// Target frame buffer
		FramebufferObject _frameBuffer;
	};
}