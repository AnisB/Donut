/**
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU Lesser General Public License as
* published by the Free Software Foundation, either version 3 of the
* License, or (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program. If not, see <http://www.gnu.org/licenses/>.
*
**/

#include "DefaultInputManager.h"

namespace Donut
{
	TDefaultInputManager::TDefaultInputManager()
	: FInitDone(false)
	{
		FKeys[TKeyCode::W] = false;
		FKeys[TKeyCode::S] = false;
		FKeys[TKeyCode::A] = false;
		FKeys[TKeyCode::D] = false;
		m_time = glfwGetTime();
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

	void TDefaultInputManager::MouseMoved(float parX, float parY)
	{
		if(!FInitDone)
		{
			oldX= parX;
			oldY= parY;
			FInitDone = true;
			return;
		}
		FCamera->Yaw((parX-oldX)*3.14/180.0*20);
		FCamera->Pitch((parY-oldY)*3.14/180.0*20);
		oldX= parX;
		oldY= parY;
	}
	void TDefaultInputManager::MousePressed(TMouseCode::Type parButton)
	{

	}
	void TDefaultInputManager::MouseReleased(TMouseCode::Type parButton)
	{
	}

	double TDefaultInputManager::Update()
	{
		double next = glfwGetTime();
		double delta = next-m_time;
		if(FKeys[TKeyCode::W])
		{
			FCamera->Translate(Vector3(0.0,0.0,delta*50));
		}
		if(FKeys[TKeyCode::S])
		{
			FCamera->Translate(Vector3(0.0,0.0,-delta*50));
		}	
		if(FKeys[TKeyCode::A])
		{
			FCamera->Translate(Vector3(delta*50,0.0,0.0));
		}
		if(FKeys[TKeyCode::D])
		{
			FCamera->Translate(Vector3(-delta*50,0.0,0.0));
		}
		m_time =  next;
		return delta;
	}
}

