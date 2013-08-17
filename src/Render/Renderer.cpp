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
#include "Square.h"
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

 	void TDonutRendererOpenGL::Init()
 	{ 	 
 		glfwMakeContextCurrent(FWindow);
 	}

 	void TDonutRendererOpenGL::Draw()
 	{ 	 
 		//Inits
        glClearColor(0.f,0.f,0.f, 0.f);
 		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
 		glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();

        for(size_t pass = 0; pass < NB_PASSES; ++pass)
        {
        	TRenderPass & passIter = FRenderPasses[pass];
        	CRITICAL_SECTION_OBJ_BEGIN(passIter);
        	passIter.Draw();
        	CRITICAL_SECTION_OBJ_END(passIter);
        }

        //SwapBuffer
        glfwSwapBuffers(FWindow);
    }

	bool TDonutRendererOpenGL::IsRendering()
	{
		return (FIsRendering.GetValue() && !glfwWindowShouldClose(FWindow));

	}

	void TDonutRendererOpenGL::SetRendering(bool parVal)
	{
		FIsRendering.SetValue(parVal);
	}


	void TDonutRendererOpenGL::RegisterToDraw(TDrawableObject * parDrawable, size_t PASS_NUMBER)
	{
		AssertRelease(PASS_NUMBER < NB_PASSES);
		TRenderPass & pass = FRenderPasses[PASS_NUMBER];
		CRITICAL_SECTION_OBJ_BEGIN(pass);
		pass.AddDrawable(parDrawable);
		CRITICAL_SECTION_OBJ_END(pass);
	}

	void TDonutRendererOpenGL::Clear()
	{
        for(size_t pass = 0; pass < NB_PASSES; ++pass)
        {
        	TRenderPass & passIter = FRenderPasses[pass];
        	CRITICAL_SECTION_OBJ_BEGIN(passIter);
        	passIter.Clear();
        	CRITICAL_SECTION_OBJ_END(passIter);
        }
	}

	// END CLASS DECLARATION
	void *CreateRenderingThread(void* parGraphicRenderer)
	{
		TDonutRendererOpenGL * realGraphicRenderer = (TDonutRendererOpenGL*) parGraphicRenderer;
		realGraphicRenderer->Init();

		while(realGraphicRenderer->IsRendering())
		{
			realGraphicRenderer->Draw();
		}
		RENDER_DEBUG_NOARGS("Window isn't rendering anymore");
		pthread_exit(0);
	}

}
