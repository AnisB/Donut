#pragma once

// Library includes
#include "graphics/shaderdata.h"
#include "graphics/material.h"
#include "resource/texture.h"

namespace donut
{
	// Foward declaration
	struct TGeometry;


	struct TBufferOutput
	{
		int width;
		int height;
		std::vector<TTextureInfo> buffers;
	};

	// Class
	class TCanvas
	{
	public:
		// Creation
		TCanvas(int _width, int _height);
		virtual ~TCanvas();
		// Init, could be in the constructor, but whatever
		virtual void Init() =  0;
		// Enabling the canvas before drawing it
		virtual void Enable() = 0;
		// Disabling the canvas after drawing it
		virtual void Disable() = 0;
		// Returns the output of this canvas
		const TBufferOutput& Result();
	protected:
		int m_width;
		int m_height;
		// GPU buffer index
		uint32_t m_frameBuffer;
		// What you will get from this canvas after drawing into it
		TBufferOutput m_output;
	};
	// END CLASS DECLARATION
}