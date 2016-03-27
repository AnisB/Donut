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
#include "Input/helper.h"
#include "Base/Macro.h"
#include "graphics/glfactory.h"
 
#include <stdlib.h>
#include <stdio.h>
 
 namespace Donut
 {

	static void error_callback(int error, const char* description)
	{
	    GRAPHICS_ERROR(error<<" "<<description);
	}

	// Class TRenderer
 	TRenderer::TRenderer()
 	: FWindowSize()
 	, FIsFullScreen(false)
 	, FWindow(NULL)
 	, FIsRendering(false)
 	, FInitDone(false)
 	{

 	}
 	TRenderer::~TRenderer()
 	{
		FIsRendering.SetValue(false);
 	}

 	bool TRenderer::CreateRenderWindow(const TGraphicsSettings& parContext)
 	{
 		if(!FInitDone)
 		{
			// Init
 			if (!glfwInit())
 			{
 				GRAPHICS_ERROR("Failed during glfw init.");
 				return false;
 			}

 			// Init error call back
			glfwSetErrorCallback(error_callback);
 			
 			// Setting the context info
			glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, parContext.major);
			glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, parContext.minor);
			glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
			glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


			// Window creation
 			FWindow = glfwCreateWindow(parContext.width, parContext.lenght, parContext.windowName.c_str(), parContext.fullScreen?glfwGetPrimaryMonitor():NULL, NULL);
 			if(FWindow==NULL)
 			{
 				GRAPHICS_ERROR("Failed creating the window: "<<parContext.width<<" "<<parContext.lenght<<" "<<parContext.windowName.c_str());
 				return false;
 			}
 			// Setting context
			glfwMakeContextCurrent(FWindow);

		    // Initiating glew
			glewExperimental = GL_TRUE;
			GLenum glewReturn = glewInit();
			if(glewReturn)
			{
			    GRAPHICS_ERROR("Glew returned: "<<glewGetErrorString(glewReturn));
 				return false;
			}
			
			#if _DEBUG
			const GLubyte* renderer = glGetString (GL_RENDERER); 
			const GLubyte* version = glGetString (GL_VERSION); 
			GRAPHICS_DEBUG("Renderer: "<<renderer);
			GRAPHICS_DEBUG("Version: "<<version);
			#endif
 			// Setting the rendering flag
 			FIsRendering.SetValue(true);
			CheckGLState(FLUSH_GL_ERROR);
			ASSERT_MSG_NO_RELEASE(CheckGLState("Check pre render"), "GL state was not clear before starting");
   			glfwSetInputMode(FWindow,GLFW_CURSOR,GLFW_CURSOR_DISABLED);
 		}
 		else
 		{
 			GRAPHICS_DEBUG("This window has already been created.");
 			ASSERT(FWindow != NULL);
 			glfwShowWindow(FWindow);
 		}
 		return true;
 	}
 	
 	void TRenderer::DestroyRenderWindow()
 	{
 		GRAPHICS_DEBUG("Destroying window.");	
 		ASSERT(FWindow != NULL);
 		glfwTerminate();
 		FWindow = NULL;
 		FInitDone = false;
 	}	

 	void TRenderer::HideRenderWindow()
 	{
 		GRAPHICS_DEBUG("Hiding window.");	
 		ASSERT(FWindow != NULL);
 		glfwHideWindow(FWindow);
 	}	

 	void TRenderer::ShowRenderWindow()
 	{
 		GRAPHICS_DEBUG("Showing window.");	
 		ASSERT(FWindow != NULL);
 		glfwShowWindow(FWindow);
 	}	

 	bool TRenderer::Init()
 	{
 		bool isOk = true;
		// Init the render thread context
		glfwMakeContextCurrent(FWindow);
 		// initing the inputs
 		InputInit();

 		SetClearColor(v4_ZERO); 
 			
		int nbPasses = m_pipeline->passes.size();
        for(size_t pass = 0; pass < nbPasses; ++pass)
        {
        	m_pipeline->passes[pass]->Init();
        }
        m_pipeline->BuildPipelineData();
		return isOk;
 	}
	void TRenderer::SetLook(const TRenderingLook::Type parLook)
	{
		if(parLook == TRenderingLook::LINE)
		{
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		}
		else if(parLook == TRenderingLook::FILL)
		{
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		}
	}

 	void TRenderer::Draw()
 	{ 	 
		// We clear the global buffer
 		ClearBuffer();
		int nbPasses = m_pipeline->passes.size();
        for(size_t pass = 0; pass < nbPasses; ++pass)
        {
        	TPass * currentPass = m_pipeline->passes[pass];
			currentPass->Bind();
			currentPass->Draw(m_pipeline->pipelineData);
			currentPass->Unbind();
        }
		// Swap front and back buffer
	  	glfwSwapBuffers (FWindow);
    }

	void TRenderer::InputInit()
	{
		glfwSetKeyCallback(FWindow, key_callback);
		glfwSetMouseButtonCallback(FWindow, mouse_button_callback);
		glfwSetScrollCallback(FWindow, mouse_scroll_callback);
		glfwSetCursorPosCallback(FWindow, mouse_pos_callback);
	}

	bool TRenderer::IsRendering()
	{
		return (FIsRendering.GetValue() && !glfwWindowShouldClose(FWindow));

	}

	void TRenderer::SetRendering(bool parVal)
	{
		FIsRendering.SetValue(parVal);
	}

	// END CLASS DECLARATION
	
	void *CreateRenderingThread(void* parGraphicRenderer)
	{
		TRenderer * realGraphicRenderer = (TRenderer*) parGraphicRenderer;
		realGraphicRenderer->Init();
		GRAPHICS_DEBUG("Init is done.");
		while(realGraphicRenderer->IsRendering())
		{
			realGraphicRenderer->Draw();
		}
		GRAPHICS_DEBUG("Window isn't rendering anymore");
		THREAD_EXIT(0);
	}
}
