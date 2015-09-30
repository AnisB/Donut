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

// ----------------------------------------
//  Includes
// ----------------------------------------
// Donut includes
#include "Engine.h"
#include <base/common.h>

// ----------------------------------------
//  Implementation
// ----------------------------------------

 namespace Donut
 {
 	Engine::Engine()
 	{
 		ENGINE_INFO("Creating the engine...");
 		FRenderer = new Donut::TRenderer();
 		ENGINE_INFO("Core engine created");
 	}
 	
 	Engine::~Engine()
 	{	
 		delete FRenderer;
 	}

 	void Engine::LaunchRendering(const TContextDetail& parContext)
 	{
 		ENGINE_INFO("Creating rendering thread...");
 		FRenderer->CreateRenderWindow(parContext);
 		InitScene();
#if __posix__
 		FThreadData = CREATE_THREAD(FTRenderingThread,CreateRenderingThread,FRenderer);
#elif WIN32
 		CREATE_THREAD(FTRenderingThread,CreateRenderingThread,FRenderer);
#endif
 		ENGINE_INFO("Redering thread created");
 	}

 	void Engine::StopRendering()
 	{
 		ENGINE_INFO("Rendering will stop...");
 		FRenderer->SetRendering(false);
 		THREAD_JOIN(FTRenderingThread, FThreadData,NULL);
 		FRenderer->DestroyRenderWindow();
 		ENGINE_INFO("Rendering stoped");
 	}

 	void Engine::PauseRendering()
 	{
 		ENGINE_INFO("Pausing rendering...");
 		FRenderer->SetRendering(false);
 		THREAD_JOIN(FTRenderingThread, FThreadData,NULL);
 		FRenderer->HideRenderWindow();
 		ENGINE_INFO("Rendering paused");

 	}

 	bool Engine::IsRendering()
 	{
 		return FRenderer->IsRendering();
 	}

	void Engine::SetVertexShader(const std::string& parVertex, int parNbPass)
	{
		FRenderer->SetVertexShader(parVertex,parNbPass);
	}

	void Engine::SetFragmentShader(const std::string& parFrag, int parNbPass)
	{
		FRenderer->SetFragmentShader(parFrag,parNbPass);
	}

 	void Engine::ResumeRendering()
 	{
 		ENGINE_INFO("Resuming rendering...");
 		FRenderer->ShowRenderWindow();
 		FRenderer->SetRendering(true);
 		FThreadData = CREATE_THREAD(FTRenderingThread,CreateRenderingThread,FRenderer);
 		ENGINE_INFO("Rendering resumed");
 	}

	void Engine::DrawObject(TDrawableObject * parObject)
 	{
 		FRenderer->RegisterToDraw(parObject);
 	}

	void Engine::RemoveObject(TDrawableObject * parObject)
 	{
 		FRenderer->UnRegisterToDraw(parObject);
 	}

 }
