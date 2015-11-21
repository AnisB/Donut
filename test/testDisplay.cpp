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

// Resources
#include <resource/sugarloader.h>
#include <resource/resourcemanager.h>
// Core
#include <core/scenenode.h>
// Render
#include <render/renderer.h>
#include <graphics/factory.h>
// Input 
#include <input/defaultinputmanager.h>
#include <input/helper.h>
// Math
#include <butter/vector3.h>
#include <butter/vector4.h>

int main()
{
	Donut::TSugarLoader::Instance().Init("data");	

	// Creating the rendering window
	Donut::TRenderer * window = new Donut::TRenderer();
	// Context info
	Donut::TGraphicsSettings newContext;
	newContext.windowName = "testDisplay";
	newContext.width = 1280;
	newContext.lenght = 720;
	newContext.major = 4;
	newContext.minor = 1;
	window->CreateRenderWindow(newContext);

	// Light source declaration
	Donut::TScene* scene = new Donut::TScene();
	scene->root = new Donut::TNode();
	Donut::TShader uniformShader("shaders/base/vertex.glsl", "shaders/base/geometry.glsl", "shaders/base/fragment.glsl");
	Donut::TMesh* cube = CreateCube(5.0, uniformShader);
	Donut::TMesh* cube2 = CreateCube(2.5, uniformShader);
	Donut::TSceneNode* node1 = new Donut::TSceneNode();
	node1->Translate(Donut::vector3(10,0, -20));
	Donut::TSceneNode* node2 = new Donut::TSceneNode();
	node2->Translate(Donut::vector3(20,0, -20));
	node1->AddDrawable(cube);
	node2->AddDrawable(cube2);
	scene->root->AttachChild(node1);
	scene->root->AttachChild(node2);

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