#pragma once

// Library includes
#include "graphics/uniformhandler.h"
#include "graphics/canvas.h"
#include "render/collector.h"

namespace donut
{
	class TDrawable
	{
	public:
		// Cst & Dst
		TDrawable();
		virtual ~TDrawable();

		// Evaluate the drawable
		virtual void Evaluate(TCollector& _collector, const bento::Matrix4& _tm) = 0;
	};
}