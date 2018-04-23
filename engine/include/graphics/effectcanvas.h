#pragma once

// Library includes
#include "canvas.h"

namespace donut
{
	class TEffectCanvas : public TCanvas
	{
	public:
		// Creation
		TEffectCanvas(int _width, int _height, const std::string& _outputName);
		virtual ~TEffectCanvas();

		// Inheritance exigences
		virtual void Init();
		virtual void Enable();
		virtual void Disable();
	protected:
		std::string m_texName;
	};
}