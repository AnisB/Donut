#pragma once

// Library includes
#include "canvas.h"

namespace donut
{
	class TEmptyCanvas : public TCanvas
	{
	public:
		// Creation
		TEmptyCanvas(int _width, int _height);
		virtual ~TEmptyCanvas();

		// Inheritance exigences
		virtual void Init();
		virtual void Enable();
		virtual void Disable();
	};
}