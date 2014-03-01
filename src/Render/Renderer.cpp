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
#include "Input/InputHelper.h"
#include "Render/Defines.h"
 #include <Render/Helper.h>
#include <stdlib.h>
#include <stdio.h>
 
 namespace Donut
 {

	static void error_callback(int error, const char* description)
	{
	    RENDER_ERR(error<<" "<<description);
	}

	// Class TRenderer
 	TRenderer::TRenderer()
 	: FWindowSize(TInt2())
 	, FIsFullScreen(false)
 	, FWindow(NULL)
 	, FIsRendering(false)
 	, FInitDone(false)
 	{

 	}
 	TRenderer::~TRenderer()
 	{
		FIsRendering.SetValue(false);
 		foreach(pass, FRenderPasses)
 		{
 			delete *pass;
 		}
 	}

 	bool TRenderer::CreateRenderWindow(const TContextDetail& parContext, size_t parNbPass)
 	{
 		if(!FInitDone)
 		{
			// Init
 			if (!glfwInit())
 			{
 				RENDER_ERR("Failed during glfw init.");
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
 				RENDER_ERR("Failed creating the window: "<<parContext.width<<" "<<parContext.lenght<<" "<<parContext.windowName.c_str());
 				return false;
 			}
 			// Setting context
			glfwMakeContextCurrent(FWindow);

		    // Initiating glew
			glewExperimental = GL_TRUE;
			GLenum glewReturn = glewInit();
			if(glewReturn)
			{
			    RENDER_ERR("Glew returned: "<<glewGetErrorString(glewReturn));
 				return false;
			}
			
			#ifdef DEBUG
			const GLubyte* renderer = glGetString (GL_RENDERER); 
			const GLubyte* version = glGetString (GL_VERSION); 
			RENDER_DEBUG("Renderer: "<<renderer);
			RENDER_DEBUG("Version: "<<version);
			#endif
 			// Setting the rendering flag
 			FIsRendering.SetValue(true);
			CheckGLState("FLUSH");
			FNbPasses = parNbPass; 
	 		for(size_t count = 0; count < FNbPasses; ++count)
	 		{
	 			FRenderPasses.push_back(new TRenderPass());
	 		}
   			glfwSetInputMode(FWindow,GLFW_CURSOR,GLFW_CURSOR_DISABLED);
 		}
 		else
 		{
 			RENDER_DEBUG("This window has already been created.");
 			AssertRelease(FWindow != NULL);
 			glfwShowWindow(FWindow);
 		}
 		return true;
 	}
 	void TRenderer::HideRenderWindow()
 	{
 		RENDER_DEBUG("Hiding window.");	
 		AssertRelease(FWindow != NULL);
 		glfwHideWindow(FWindow);
 	}	

 	void TRenderer::ShowRenderWindow()
 	{
 		RENDER_DEBUG("Showing window.");	
 		AssertRelease(FWindow != NULL);
 		glfwShowWindow(FWindow);
 	}	

 	void TRenderer::DestroyRenderWindow()
 	{
 		RENDER_DEBUG("Destroying window.");	
 		AssertRelease(FWindow != NULL);
 		glfwTerminate();
 		FWindow = NULL;
 		FInitDone = false;

 	}	

 	bool TRenderer::Init()
 	{
 		bool isOk = true;
		// Init the render thread context
		glfwMakeContextCurrent(FWindow);
 		// initing the inputs
 		InputInit();
		foreach(pass,FRenderPasses)
		{
			(*pass)->Init();
		}
 		glClearColor(0.0,0.0,0.0,0.0); 	
 		//glEnable(GL_CULL_FACE);
		//glCullFace(GL_FRONT_AND_BACK);
		return isOk;
 	}

 	void TRenderer::Draw()
 	{ 	 
 		//Inits
 		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        for(size_t pass = 0; pass < FNbPasses; ++pass)
        {
        	TRenderPass & passIter = (*FRenderPasses[pass]);
        	passIter.Draw();
        }
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


	void TRenderer::RegisterToDraw(TDrawableObject * parDrawable, size_t PASS_NUMBER)
	{
		AssertRelease(PASS_NUMBER < FNbPasses);
		TRenderPass  & pass = (*FRenderPasses[PASS_NUMBER]);
		CRITICAL_SECTION_OBJ_BEGIN(pass);
		pass.AddDrawable(parDrawable);
		CRITICAL_SECTION_OBJ_END(pass);
	}

	void TRenderer::UnRegisterToDraw(TDrawableObject * parDrawable, size_t PASS_NUMBER)
	{
		AssertRelease(PASS_NUMBER < FNbPasses);
		TRenderPass & pass = (*FRenderPasses[PASS_NUMBER]);
		CRITICAL_SECTION_OBJ_BEGIN(pass);
		pass.RemoveDrawable(parDrawable);
		CRITICAL_SECTION_OBJ_END(pass);
	}

	void TRenderer::Clear()
	{
        for(size_t pass = 0; pass < FNbPasses; ++pass)
        {
        	TRenderPass & passIter = (*FRenderPasses[pass]);
        	CRITICAL_SECTION_OBJ_BEGIN(passIter);
        	passIter.Clear();
        	CRITICAL_SECTION_OBJ_END(passIter);
        }
	}

	TNode* TRenderer::GetRoot(int parNbPass)
	{
		return FRenderPasses[parNbPass]->GetRoot();
	}
	Camera* TRenderer::GetCamera(int parNbPass)
	{
		return FRenderPasses[parNbPass]->GetCamera();
	}
	void TRenderer::SetVertexShader(const std::string& parVertex, int parNbPass)
	{
		FRenderPasses[parNbPass]->SetVertexShader(parVertex);
	}

	void TRenderer::SetFragmentShader(const std::string& parFrag, int parNbPass)
	{
		FRenderPasses[parNbPass]->SetFragmentShader(parFrag);
	}
	
	void TRenderer::SetRenderType(FrameCanvasContent::Type parType, int parNbPass)
	{
		FRenderPasses[parNbPass]->SetRenderType(parType);
	}

	void TRenderer::AddLight(TLight* parLight, int parNbPass)
	{
		FRenderPasses[parNbPass]->AddLight(parLight);
	}
	// END CLASS DECLARATION
	
	void *CreateRenderingThread(void* parGraphicRenderer)
	{
		TRenderer * realGraphicRenderer = (TRenderer*) parGraphicRenderer;
		realGraphicRenderer->Init();
		RENDER_DEBUG("Init is done.");
		while(realGraphicRenderer->IsRendering())
		{
			realGraphicRenderer->Draw();
		}
		RENDER_DEBUG("Window isn't rendering anymore");
		pthread_exit(0);
	}
}
