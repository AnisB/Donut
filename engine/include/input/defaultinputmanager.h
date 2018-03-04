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
#ifndef DEFAULT_INPUT_MANAGER_DONUT 
#define DEFAULT_INPUT_MANAGER_DONUT

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
		double m_oldX;
		double m_oldY;
		double m_time;
		std::map<TKeyCode::Type, bool> FKeys;
	};
}

#endif //DEFAULT_INPUT_MANAGER_DONUT