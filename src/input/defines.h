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

#ifndef DONUT_INPUT_H
#define DONUT_INPUT_H

#include <render/common.h>

namespace Donut
{
	namespace TKeyCode
	{
		enum Type
		{
			// Letters
			A=GLFW_KEY_A,
			B=GLFW_KEY_B,  
			C=GLFW_KEY_C,  
			D=GLFW_KEY_D,  
			E=GLFW_KEY_E,  
			F=GLFW_KEY_F,  
			G=GLFW_KEY_G,  
			H=GLFW_KEY_H,  
			I=GLFW_KEY_I,  
			J=GLFW_KEY_J,  
			K=GLFW_KEY_K,  
			L=GLFW_KEY_L,  
			M=GLFW_KEY_M,  
			N=GLFW_KEY_N,  
			O=GLFW_KEY_O,  
			P=GLFW_KEY_P,  
			Q=GLFW_KEY_Q,  
			R=GLFW_KEY_R,  
			S=GLFW_KEY_S,  
			T=GLFW_KEY_T,  
			U=GLFW_KEY_U,  
			V=GLFW_KEY_V,  
			W=GLFW_KEY_W,  
			X=GLFW_KEY_X,  
			Y=GLFW_KEY_Y,  
			Z=GLFW_KEY_Z,  
			// Directions
			RIGHT=GLFW_KEY_RIGHT,
	 		LEFT=GLFW_KEY_LEFT,
			DOWN=GLFW_KEY_DOWN,
			UP=GLFW_KEY_UP,
			// Other
			ESCAPE = GLFW_KEY_ESCAPE
		};
	}

	namespace TMouseCode
	{
		enum Type
		{
			BUTTON_1=GLFW_MOUSE_BUTTON_1,
			BUTTON_2=GLFW_MOUSE_BUTTON_2,
			BUTTON_3=GLFW_MOUSE_BUTTON_3,
			BUTTON_4=GLFW_MOUSE_BUTTON_4,
			BUTTON_5=GLFW_MOUSE_BUTTON_5,
			BUTTON_6=GLFW_MOUSE_BUTTON_6,
			BUTTON_7=GLFW_MOUSE_BUTTON_7,
			BUTTON_8=GLFW_MOUSE_BUTTON_8,
		};
	}
}


#endif // DONUT_INPUT_H
