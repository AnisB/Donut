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
 #ifndef INPUT_HELPER_DONUT 
 #define INPUT_HELPER_DONUT



 #include "Defines.h"
 #include "Render/Defines.h"

 namespace Donut
 {
 	// Keyboard
 	void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

 	//Mouse
 	void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
 	void mouse_scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
 	void mouse_pos_callback(GLFWwindow* window, double xpos, double ypos);


 	//Joystick

 }
 #endif //INPUT_HELPER_DONUT