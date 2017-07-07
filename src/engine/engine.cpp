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
// donut includes
#include "Engine.h"
#include "engine/common.h"

// ----------------------------------------
//  Implementation
// ----------------------------------------

namespace donut
{
 	TEngine::TEngine()
 	: FRenderingRunning(false)
 	, m_scene(nullptr)
 	, _rendering_thread(nullptr)
 	{
 		FRenderer = new TRenderer();
 		ENGINE_INFO("Engine created");
 	}
 	
 	TEngine::~TEngine()
 	{	
 		if(_rendering_thread)
 		{
 			delete _rendering_thread;
 			_rendering_thread = nullptr;
 		}

 		delete FRenderer;
 	}

 	void TEngine::LaunchRendering(const TGraphicsSettings& parContext)
 	{
 		ASSERT_MSG_NO_RELEASE(!FRenderingRunning, "Rendering already launched, it is just paused.");
 		TPipeline* pipeline = GenerateGraphicPipeline(m_scene, parContext.width, parContext.lenght);
 		FRenderer->CreateRenderWindow(parContext);
 		FRenderer->SetPipeline(pipeline);
 		InitScene();

 		_rendering_thread = new std::thread(CreateRenderingThread, FRenderer);
 		ENGINE_INFO("Redering thread created");
 		FRenderingRunning = true;
 		
 	}

 	void TEngine::StopRendering()
 	{
 		FRenderer->SetRendering(false);
 		_rendering_thread->join();
 		delete _rendering_thread;
 		_rendering_thread = nullptr;
 		FRenderer->DestroyRenderWindow();
 		ENGINE_INFO("Rendering stoped");
 		FRenderingRunning = false;
 	}

 	void TEngine::PauseRendering()
 	{
 		FRenderer->SetRendering(false);
 		_rendering_thread->join();
 		delete _rendering_thread;
 		_rendering_thread = nullptr;
 		FRenderer->HideRenderWindow();
 		ENGINE_INFO("Rendering paused");

 	}

 	void TEngine::ResumeRendering()
 	{
 		ASSERT_MSG_NO_RELEASE(FRenderingRunning, "Rendering is not launched.")
 		FRenderer->ShowRenderWindow();
 		FRenderer->SetRendering(true);
 		_rendering_thread = new std::thread(CreateRenderingThread, FRenderer);
 		ENGINE_INFO("Rendering resumed");
 	}

 	bool TEngine::IsRendering()
 	{
 		return FRenderer->IsRendering();
 	}

	void TEngine::Update(float dt)
	{
		FarmEvents();
	}
}