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

// Donut includes
#include <base/common.h>
#include "inputhelper.h"
#include "defaultinputmanager.h"

namespace Donut
{
	// The library input manager
 	static TInputManager* InManager = new TDefaultInputManager();

 	void SetInputManager(TInputManager* _inputManager)
 	{
 		INPUT_INFO("Input manager has changed");
 		if(InManager!=NULL)
 			delete InManager;
 		InManager = _inputManager;
 	}
	TInputManager*  GetInputManager()
	{
		return InManager;
	}
	void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
	{
	    ASSERT_NO_RELEASE(InManager != NULL);
	    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	    {
	        glfwSetWindowShouldClose(window, GL_TRUE);
	    }
	    if(action == GLFW_PRESS)
	    {
		    InManager->KeyPressed((TKeyCode::Type)key);
	    }
	    else if(action == GLFW_RELEASE)
	    {
		    InManager->KeyReleased((TKeyCode::Type)key);
	    }
	}	

 	void FarmEvents()
 	{
	  	glfwPollEvents();
 	}

 	void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
 	{
	    ASSERT_NO_RELEASE(InManager != NULL);
	    if(action == GLFW_PRESS)
	    {
		    InManager->MousePressed((TMouseCode::Type)button);
	    }
	    else if(action == GLFW_RELEASE)
	    {
		    InManager->MouseReleased((TMouseCode::Type)button);
	    }
 	}
 	
 	void mouse_scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
 	{

 	}

 	void mouse_pos_callback(GLFWwindow* window, double xpos, double ypos)
 	{
	    ASSERT_NO_RELEASE(InManager != NULL);
	    int width, height;
	    glfwGetFramebufferSize(window, &width, &height);
	    float ratio = width / (float) height;
	    float x = ratio*(2*xpos/(float)width - 1);
	    float y = 2*-ypos/(float)height + 1;
	    InManager->MouseMoved(x,y);
 	}
}