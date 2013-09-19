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
 		DEFAULT_DEBUG_NOARGS("Creating the engine");
 		FRenderer = new Donut::TDonutRenderer();
 		DEFAULT_DEBUG_NOARGS("Core engine created");
 	}
 	
 	Engine::~Engine()
 	{	
 		delete FRenderer;
 	}

 	void Engine::LaunchRendering()
 	{
 		DEFAULT_DEBUG_NOARGS("creating rendering thread");
 		FRenderer->CreateRenderWindow(float2(DEFAULTW,DEFAULTL),DEFAULTNAME, DEFAULTFULLSCREEN);
 		FThreadData = CREATE_THREAD(FTRenderingThread,CreateRenderingThread,FRenderer);
 		DEFAULT_DEBUG_NOARGS("Redering thread created");
 	}

 	void Engine::StopRendering()
 	{
 		DEFAULT_DEBUG_NOARGS("Trying to stop rendering");
 		FRenderer->SetRendering(false);
 		THREAD_JOIN(FTRenderingThread, FThreadData,NULL);
 		FRenderer->DestroyRenderWindow();
 		DEFAULT_DEBUG_NOARGS("Rendering destroyed");
 	}

 	void Engine::PauseRendering()
 	{
 		DEFAULT_DEBUG_NOARGS("Pause rendering");
 		FRenderer->SetRendering(false);
 		THREAD_JOIN(FTRenderingThread, FThreadData,NULL);
 		FRenderer->HideRenderWindow();
 		DEFAULT_DEBUG_NOARGS("Rendering paused");

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
 		DEFAULT_DEBUG_NOARGS("Resuming rendering");
 		FRenderer->ShowRenderWindow();
 		FRenderer->SetRendering(true);
 		FThreadData = CREATE_THREAD(FTRenderingThread,CreateRenderingThread,FRenderer);
 		DEFAULT_DEBUG_NOARGS("Rendering resumed");
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
