#include "input/DefaultInputManager.h"
#include "gpu_backend/gl_backend.h"

// Bento includes
#include <bento_math/vector3.h>

namespace donut
{
	TDefaultInputManager::TDefaultInputManager()
	: m_initDone(false)
	{
		FKeys[TKeyCode::W] = false;
		FKeys[TKeyCode::S] = false;
		FKeys[TKeyCode::A] = false;
		FKeys[TKeyCode::D] = false;
		m_time = gl::get_time();
	}

	TDefaultInputManager::~TDefaultInputManager()
	{

	}

	void TDefaultInputManager::KeyPressed(TKeyCode::Type parKey)
	{
		FKeys[parKey] = true;
	}
	void TDefaultInputManager::KeyReleased(TKeyCode::Type parKey)
	{
		FKeys[parKey] = false;
	}

	void TDefaultInputManager::MouseMoved(double parX, double parY)
	{
		if(!m_initDone)
		{
			m_oldX= parX;
			m_oldY= parY;
			m_initDone = true;
			return;
		}
		FCamera->Yaw((parX-m_oldX)*3.14/180.0*20);
		FCamera->Pitch((parY-m_oldY)*3.14/180.0*20);
		m_oldX= parX;
		m_oldY= parY;
	}
	void TDefaultInputManager::MousePressed(TMouseCode::Type parButton)
	{

	}
	void TDefaultInputManager::MouseReleased(TMouseCode::Type parButton)
	{
	}

	double TDefaultInputManager::Update()
	{
		double next = gl::get_time();
		double delta = next-m_time;
		if(FKeys[TKeyCode::W])
		{
			FCamera->Translate(bento::vector3(0.0,0.0,delta*1));
		}
		if(FKeys[TKeyCode::S])
		{
			FCamera->Translate(bento::vector3(0.0,0.0,-delta*1));
		}	
		if(FKeys[TKeyCode::A])
		{
			FCamera->Translate(bento::vector3(delta*1,0.0,0.0));
		}
		if(FKeys[TKeyCode::D])
		{
			FCamera->Translate(bento::vector3(-delta*1,0.0,0.0));
		}
		m_time =  next;
		return delta;
	}
}

