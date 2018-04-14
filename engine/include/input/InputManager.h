#pragma once

#include "defines.h"

namespace donut
{
	class TInputManager
	{
	public:
		TInputManager();
		virtual ~TInputManager();

		virtual void KeyPressed(TKeyCode::Type parKey) = 0;
		virtual void KeyReleased(TKeyCode::Type parKey) = 0;

		virtual void MouseMoved(double parX, double parY) = 0;
		virtual void MousePressed(TMouseCode::Type parButton) = 0;
		virtual void MouseReleased(TMouseCode::Type parButton) = 0;
	};
}