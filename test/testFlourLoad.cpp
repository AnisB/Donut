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

#include <graphics/pipeline.h>
#include <Render/Renderer.h>
#include <Input/helper.h>
#include <Input/DefaultInputManager.h>
#include <Input/InputManager.h>
#include <resource/sugar_loader.h>
#include <resource/resourcemanager.h>
#include <resource/flourLoader.h>
#include <graphics/factory.h>
#include <graphics/gl_backend.h>

#include <core/scenenode.h>
#include <butter/vector3.h>
#include <butter/vector4.h>

int main(int argc, char** argv)
{
	STRING_TYPE sceneName;
	if (argc == 3)
	{
		sceneName = argv[2];
		donut::ResourceManager::Instance().Init(argv[1]);
	}
	else
	{
		sceneName = "TeapotArmy";
		donut::ResourceManager::Instance().Init("assets");
	}

	// Creating the rendering window
	donut::TRenderer * window = new donut::TRenderer();
	// Context info
	donut::TGraphicsSettings newContext = donut::GL::default_settings();
	newContext.window_name = "testFlourLoad";
	window->CreateRenderWindow(newContext);

	donut::TFlour* flour = donut::GenerateFlour(sceneName);
	donut::TPipeline* renderingPipeline;
	renderingPipeline = donut::GenerateGraphicPipeline(flour, newContext.width, newContext.lenght);
	window->SetPipeline(renderingPipeline);
	window->Init();
	
	donut::Camera* camera = renderingPipeline->camera;
	donut::TDefaultInputManager* inManager = static_cast<donut::TDefaultInputManager*>(donut::GetInputManager());
	inManager->FCamera = camera;
	camera->DefinePerspective(45.0, newContext.width/(double)newContext.lenght,1.0,2000.0);
	
	while(window->IsRendering())
	{
		window->Draw();
		donut::FarmEvents();
		inManager->Update();
	}

	delete window;
	return 0;
}