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

#include "Engine.h"

// ----------------------------------------
//  Implementation
// ----------------------------------------

 namespace Donut
 {
 	Engine::Engine()
 	{
 		DEFAULT_DEBUG("Creating the engine.");
 		FRenderer = new Donut::TRenderer();
 		DEFAULT_DEBUG("Core engine created.");
 	}
 	
 	Engine::~Engine()
 	{	
 		delete FRenderer;
 	}

 	void Engine::LaunchRendering(const TContextDetail& parContext)
 	{
 		DEFAULT_DEBUG("creating rendering thread");
 		FRenderer->CreateRenderWindow(parContext);
 		FThreadData = CREATE_THREAD(FTRenderingThread,CreateRenderingThread,FRenderer);
 		DEFAULT_DEBUG("Redering thread created");
 	}

 	void Engine::StopRendering()
 	{
 		DEFAULT_DEBUG("Trying to stop rendering");
 		FRenderer->SetRendering(false);
 		THREAD_JOIN(FTRenderingThread, FThreadData,NULL);
 		FRenderer->DestroyRenderWindow();
 		DEFAULT_DEBUG("Rendering destroyed");
 	}

 	void Engine::PauseRendering()
 	{
 		DEFAULT_DEBUG("Pause rendering");
 		FRenderer->SetRendering(false);
 		THREAD_JOIN(FTRenderingThread, FThreadData,NULL);
 		FRenderer->HideRenderWindow();
 		DEFAULT_DEBUG("Rendering paused");

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
 		DEFAULT_DEBUG("Resuming rendering");
 		FRenderer->ShowRenderWindow();
 		FRenderer->SetRendering(true);
 		FThreadData = CREATE_THREAD(FTRenderingThread,CreateRenderingThread,FRenderer);
 		DEFAULT_DEBUG("Rendering resumed");
 	}

	void Engine::DrawObject(TDrawableObject * parObject)
 	{
 		FRenderer->RegisterToDraw(parObject);
 	}

	void Engine::RemoveObject(TDrawableObject * parObject)
 	{
 		FRenderer->UnRegisterToDraw(parObject);
 	}

	void Engine::Flush()
 	{
 		FRenderer->Clear();
 	}
 }
