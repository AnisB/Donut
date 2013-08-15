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

 namespace Donut
 {

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

			// Window size
 			FWindow = glfwCreateWindow(parWindowSize.x, parWindowSize.y, parWindowName.c_str(), NULL, NULL);

 			FIsRendering.SetValue(true);
 			glfwShowWindow(FWindow);
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
		glfwSwapBuffers(FWindow);
	}


	void TDonutRendererOpenGL::Reshape()
	{ 	 
	}


		bool TDonutRendererOpenGL::IsRendering()
		{
			return FIsRendering.GetValue();
		}

		void TDonutRendererOpenGL::SetRendering(bool parVal)
		{
			FIsRendering.SetValue(parVal);
		}

		// END CLASS DECLARATION
	void *CreateRenderingThread(void* parGraphicRenderer)
	{
		TDonutRendererOpenGL * realGraphicRenderer = (TDonutRendererOpenGL*) parGraphicRenderer;
		while(realGraphicRenderer->IsRendering())
		{
			realGraphicRenderer->Draw();
			realGraphicRenderer->Reshape();
		}
		pthread_exit(0);
	}

}
