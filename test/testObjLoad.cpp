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
#include <resource/sugarloader.h>
#include <resource/resourcemanager.h>
#include <graphics/factory.h>
 
#include <core/scenenode.h>
#include <butter/vector3.h>
#include <butter/vector4.h>

int main(int argc, char** argv)
{
	ASSERT(argc == 2);
	Donut::TSugarLoader::Instance().Init("data");	

	// Creating the rendering window
	Donut::TRenderer * window = new Donut::TRenderer();
	// Context info
	Donut::TGraphicsSettings newContext;
	newContext.windowName = "testSugarLoad";
	newContext.width = 1280;
	newContext.lenght = 720;
	newContext.major = 4;
	newContext.minor = 1;
	window->CreateRenderWindow(newContext);

	Donut::TScene* scene = new Donut::TScene();
	scene->root = new Donut::TNode();
	Donut::TMesh* sugar = Donut::CreateSugarInstance(argv[1]);
	Donut::TSceneNode* node = new Donut::TSceneNode();
	node->AddDrawable(sugar);
	scene->root->AttachChild(node);

	Donut::TPipeline* renderingPipeline = Donut::GenerateGraphicPipeline(scene, newContext.width, newContext.lenght, Donut::TPipelineConfig::MINIMAL);
	window->SetPipeline(renderingPipeline);
	window->Init();
	
	Donut::Camera* camera = renderingPipeline->camera;
	Donut::TDefaultInputManager* inManager = static_cast<Donut::TDefaultInputManager*>(Donut::GetInputManager());
	inManager->FCamera = camera;
	camera->DefinePerspective(45.0,1280.0/720.0,1.0,2000.0);
	
	while(window->IsRendering())
	{
		window->Draw();
		Donut::FarmEvents();
		inManager->Update();
	}

	delete window;
	return 0;
}