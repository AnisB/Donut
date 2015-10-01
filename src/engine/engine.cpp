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
 	TEngine::TEngine()
 	: FRenderingRunning(false)
 	{
 		FRenderer = new Donut::TRenderer();
 		ENGINE_INFO("Engine created");
 	}
 	
 	TEngine::~TEngine()
 	{	
 		delete FRenderer;
 	}

 	void TEngine::LaunchRendering(const TContextDetail& parContext)
 	{
 		ASSERT_MSG_NO_RELEASE(!FRenderingRunning, "Rendering already launched, it is just paused.")
 		FRenderer->CreateRenderWindow(parContext);
 		InitScene();
 		FThreadData = CREATE_THREAD(FTRenderingThread,CreateRenderingThread,FRenderer);
 		ENGINE_INFO("Redering thread launched");
 		FRenderingRunning = true;
 	}

 	void TEngine::StopRendering()
 	{
 		FRenderer->SetRendering(false);
 		THREAD_JOIN(FTRenderingThread, FThreadData, NULL);
 		FRenderer->DestroyRenderWindow();
 		ENGINE_INFO("Rendering stoped");
 		FRenderingRunning = false;
 	}

 	void TEngine::PauseRendering()
 	{
 		FRenderer->SetRendering(false);
 		THREAD_JOIN(FTRenderingThread, FThreadData,NULL);
 		FRenderer->HideRenderWindow();
 		ENGINE_INFO("Rendering paused");

 	}

 	void TEngine::ResumeRendering()
 	{
 		ASSERT_MSG_NO_RELEASE(FRenderingRunning, "Rendering is not launched.")
 		FRenderer->ShowRenderWindow();
 		FRenderer->SetRendering(true);
 		FThreadData = CREATE_THREAD(FTRenderingThread, CreateRenderingThread, FRenderer);
 		ENGINE_INFO("Rendering resumed");
 	}

 	bool TEngine::IsRendering()
 	{
 		return FRenderer->IsRendering();
 	}

	void TEngine::SetVertexShader(const std::string& parVertex, int parNbPass)
	{
		FRenderer->SetVertexShader(parVertex, parNbPass);
	}

	void TEngine::SetFragmentShader(const std::string& parFrag, int parNbPass)
	{
		FRenderer->SetFragmentShader(parFrag, parNbPass);
	}

	void TEngine::Update(float dt)
	{
		FarmEvents();
	}

	void TEngine::DrawObject(TDrawableObject * parObject)
 	{
 		FRenderer->RegisterToDraw(parObject);
 	}

	void TEngine::RemoveObject(TDrawableObject * parObject)
 	{
 		FRenderer->UnRegisterToDraw(parObject);
 	}
}
