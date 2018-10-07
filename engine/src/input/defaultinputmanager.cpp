#include "input/DefaultInputManager.h"

// Bento includes
#include <bento_math/const.h>
#include <bento_math/vector3.h>

// External includes
#include <algorithm>

#undef max
#undef min

namespace donut
{
	TDefaultInputManager::TDefaultInputManager()
	: m_initDone(false)
	, _gpuBackend(nullptr)
	, _cameraSpeed(4.0f)
	{
		FKeys[TKeyCode::W] = false;
		FKeys[TKeyCode::S] = false;
		FKeys[TKeyCode::A] = false;
		FKeys[TKeyCode::D] = false;
		FKeys[TKeyCode::PAGE_DOWN] = false;
		m_time = -1.0f;
	}

	TDefaultInputManager::~TDefaultInputManager()
	{

	}

	void TDefaultInputManager::init(const GPUBackendAPI* backendAPI)
	{
		_gpuBackend = backendAPI;
		m_time = _gpuBackend->render_system_api.get_time(0);
	}

	void TDefaultInputManager::KeyPressed(TKeyCode::Type parKey)
	{
		FKeys[parKey] = true;
		if (parKey == TKeyCode::PAGE_UP)
		{
			_cameraSpeed = std::max(4.0f, 2.0f * _cameraSpeed);
		}

		if (parKey == TKeyCode::PAGE_DOWN)
		{
			_cameraSpeed = std::min(0.1f, 0.5f * _cameraSpeed);
		}
	}
	void TDefaultInputManager::KeyReleased(TKeyCode::Type parKey)
	{
		FKeys[parKey] = false;
	}

	void TDefaultInputManager::MouseMoved(double parX, double parY)
	{
		if(!m_initDone)
		{
			m_oldX = (float)parX;
			m_oldY = (float)parY;
			m_initDone = true;
			return;
		}
		FCamera->Yaw(((float)parX-m_oldX) * PI_OVER_180 * 20.0f);
		FCamera->Pitch(((float)parY-m_oldY) * PI_OVER_180 * 20.0f);
		m_oldX = (float)parX;
		m_oldY = (float)parY;
	}
	void TDefaultInputManager::MousePressed(TMouseCode::Type parButton)
	{

	}
	void TDefaultInputManager::MouseReleased(TMouseCode::Type parButton)
	{
	}

	double TDefaultInputManager::Update()
	{
		assert_msg(_gpuBackend != nullptr, "Uninitialized GPU backend API");
		float next = _gpuBackend->render_system_api.get_time(0);
		float delta = next-m_time;

		float displacement = _cameraSpeed * delta;
		if(FKeys[TKeyCode::W])
		{
			FCamera->Translate(bento::vector3(0.0,0.0, displacement));
		}
		if(FKeys[TKeyCode::S])
		{
			FCamera->Translate(bento::vector3(0.0,0.0,-displacement));
		}	
		if(FKeys[TKeyCode::A])
		{
			FCamera->Translate(bento::vector3(displacement,0.0,0.0));
		}
		if(FKeys[TKeyCode::D])
		{
			FCamera->Translate(bento::vector3(-displacement,0.0,0.0));
		}
		m_time =  next;
		return delta;
	}
}

