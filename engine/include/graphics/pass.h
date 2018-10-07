#pragma once

// Library includes
#include "graphics/canvas.h"

// Bento includes
#include <bento_collection/dynamic_string.h>

// STL includes
#include <vector>
 
 namespace donut
 {
	class TPass
	{
	public:
		// Constructor destructor
		TPass(const char* passName, bento::IAllocator& allocator, const GPUBackendAPI* gpuBackend)
		: _allocator(allocator)
		, _name(allocator, passName)
		, _gpuBackendAPI(gpuBackend)
		{
		}
		virtual ~TPass() {}

		const char* name() { return _name.c_str(); }

		// Allocating all the CPU and GPU required memory
		virtual void Init() = 0;
		// Setting and disabling the canvas
		virtual void Bind() = 0;
		virtual void Unbind() = 0;

		// Render the VFX (using the canvas data)
		virtual void Draw(const TFrameBufferOutput& _previousData) = 0;

		// Getting the pass output
		virtual const TFrameBufferOutput* GetOutput() = 0;

	protected:
		// Allocator for this pass
		bento::IAllocator& _allocator;
		bento::DynamicString _name;

		// Reference to the target backend gpu api to use
		const GPUBackendAPI* _gpuBackendAPI;
	};
 }