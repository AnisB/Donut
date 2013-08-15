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


#include "Renderer.h"

#include "Base/Common.h"
 	#include <stdlib.h>
#include <stdio.h>
 
 namespace Donut
 {

static void error_callback(int error, const char* description)
{
    fputs(description, stderr);
}


	// Class TDonutRendererOpenGL
 	TDonutRendererOpenGL::TDonutRendererOpenGL()
 	: FWindowSize(float2())
 	, FIsFullScreen(false)
 	, FWindow(NULL)
 	, FIsRendering(false)
 	, FInitDone(false)
 	{

 	}
 	TDonutRendererOpenGL::~TDonutRendererOpenGL()
 	{

 	}

 	void TDonutRendererOpenGL::CreateRenderWindow(const float2& parWindowSize, const std::string& parWindowName, bool parIsFullScreen)
 	{
 		if(!FInitDone)
 		{

			// Init
 			if (!glfwInit())
 			{
 				RENDER_DEBUG_NOARGS("Failed creating the window");
 				return ;

 			}
 			glfwSetErrorCallback(error_callback);

			// Window size
 			FWindow = glfwCreateWindow(parWindowSize.x, parWindowSize.y, parWindowName.c_str(), NULL, NULL);

 			FIsRendering.SetValue(true);
 			glfwShowWindow(FWindow);
 			glEnable(GL_DEPTH_TEST);
 			glfwMakeContextCurrent(FWindow);
 			RENDER_DEBUG_NOARGS("Window created");

 		}
 		else
 		{
 			RENDER_DEBUG_NOARGS("This window has already been created.");
 			AssertRelease(FWindow != NULL);
 			glfwShowWindow(FWindow);
 		}
 	}
 	void TDonutRendererOpenGL::HideRenderWindow()
 	{
 		RENDER_DEBUG_NOARGS("Hiding window.");	
 		AssertRelease(FWindow != NULL);
 		glfwHideWindow(FWindow);
 	}	

 	void TDonutRendererOpenGL::ShowRenderWindow()
 	{
 		RENDER_DEBUG_NOARGS("Showing window.");	
 		AssertRelease(FWindow != NULL);
 		glfwShowWindow(FWindow);
 	}	

 	void TDonutRendererOpenGL::DestroyRenderWindow()
 	{
 		RENDER_DEBUG_NOARGS("Destroying window.");	
 		AssertRelease(FWindow != NULL);
 		glfwTerminate();
 		FWindow = NULL;
 		FInitDone = false;

 	}	

 	void TDonutRendererOpenGL::Draw()
 	{ 	 

        float ratio;
        int width, height;
        glfwGetFramebufferSize(FWindow, &width, &height);
        ratio = width / (float) height;
        glViewport(0, 0, width, height);
        glClear(GL_COLOR_BUFFER_BIT);
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glOrtho(-ratio, ratio, -1.f, 1.f, 1.f, -1.f);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        glRotatef((float) glfwGetTime() * 50.f, 0.f, 0.f, 1.f);
        glBegin(GL_TRIANGLES);
        glColor3f(1.f, 0.f, 0.f);
        glVertex3f(-0.6f, -0.4f, 0.f);
        glColor3f(0.f, 1.f, 0.f);
        glVertex3f(0.6f, -0.4f, 0.f);
        glColor3f(0.f, 0.f, 1.f);
        glVertex3f(0.f, 0.6f, 0.f);
        glEnd();
        glfwSwapBuffers(FWindow);
}


	void TDonutRendererOpenGL::Reshape()
	{ 	 
	}


	bool TDonutRendererOpenGL::IsRendering()
	{
		return (FIsRendering.GetValue() or !glfwWindowShouldClose(FWindow));
	}

	void TDonutRendererOpenGL::SetRendering(bool parVal)
	{
		FIsRendering.SetValue(parVal);
	}
	//Called when a key is pressed

	// END CLASS DECLARATION
	void *CreateRenderingThread(void* parGraphicRenderer)
	{
		TDonutRendererOpenGL * realGraphicRenderer = (TDonutRendererOpenGL*) parGraphicRenderer;
		while(realGraphicRenderer->IsRendering())
		{
			realGraphicRenderer->Draw();
		}
		RENDER_DEBUG_NOARGS("Window isn't rendering anymore");
		pthread_exit(0);
	}

}
