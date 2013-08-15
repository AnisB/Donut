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
 		FOpenGLRenderer = new Donut::TDonutRendererOpenGL();
 	}
 	
 	Engine::~Engine()
 	{	
 		delete FOpenGLRenderer;
 	}

 	void Engine::LaunchRendering()
 	{
 		FOpenGLRenderer->CreateRenderWindow(float2(DEFAULTW,DEFAULTL),DEFAULTNAME, DEFAULTFULLSCREEN);
 		FThreadData = CREATE_THREAD(FTRenderingThread,CreateRenderingThread,FOpenGLRenderer);
 	}

 	void Engine::StopRendering()
 	{
 		FOpenGLRenderer->SetRendering(false);
 		THREAD_JOIN(FTRenderingThread, FThreadData,NULL);
 		FOpenGLRenderer->DestroyRenderWindow();
 	}

 	void Engine::PauseRendering()
 	{
 		FOpenGLRenderer->SetRendering(false);
 		THREAD_JOIN(FTRenderingThread, FThreadData,NULL);
 		FOpenGLRenderer->HideRenderWindow();
 	}

 	void Engine::ResumeRendering()
 	{
 		FOpenGLRenderer->ShowRenderWindow();
 		FOpenGLRenderer->SetRendering(true);
 		CREATE_THREAD(FTRenderingThread,CreateRenderingThread,FOpenGLRenderer);
 	}
 }
