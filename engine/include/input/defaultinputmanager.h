#pragma once

// donut includes
#include "inputManager.h"
#include "core/camera.h"

// STL includes
#include <map>

namespace donut
{
	class TDefaultInputManager : public TInputManager
	{

	public:
		TDefaultInputManager();
		virtual ~TDefaultInputManager();

		void init(const GPUBackendAPI* backendAPI);

		void KeyPressed(TKeyCode::Type parKey);
		void KeyReleased(TKeyCode::Type parKey);

		void MouseMoved(double parX, double parY);
		void MousePressed(TMouseCode::Type parButton);
		void MouseReleased(TMouseCode::Type parButton);
		double Update();

	public:
		Camera* FCamera;

	protected:
		bool m_initDone;
		float m_oldX;
		float m_oldY;
		float m_time;
		float _cameraSpeed;
		std::map<TKeyCode::Type, bool> FKeys;
		const GPUBackendAPI* _gpuBackend;
	};
}