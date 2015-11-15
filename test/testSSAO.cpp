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
#include <Input/InputHelper.h>
#include <Input/DefaultInputManager.h>
#include <Input/InputManager.h>
#include <resource/sugarloader.h>
#include <resource/resourcemanager.h>
#include <graphics/factory.h>
 
#include <core/scenenode.h>
#include <butter/vector3.h>
#include <butter/vector4.h>

int main()
{
	Donut::TSugarLoader::Instance().Init("data");	

	// Creating the rendering window
	Donut::TRenderer * window = new Donut::TRenderer();
	// Context info
	Donut::TGraphicsSettings newContext;
	newContext.windowName = "testSSAO";
	newContext.width = 1280;
	newContext.lenght = 720;
	newContext.major = 4;
	newContext.minor = 1;
	window->CreateRenderWindow(newContext);

	// Light source declaration
	Donut::TScene* scene = new Donut::TScene();
	Donut::TLight* lightSource = new Donut::TLight();
	lightSource->SetPosition(Donut::vector3(0,20,0));
	lightSource->SetDiffuse(Donut::vector4(0,0,1,1.0));
	scene->lights.push_back(lightSource);

	Donut::TLight* lightSource2 = new Donut::TLight();
	lightSource2->SetPosition(Donut::vector3(0.0,20,-120));
	lightSource2->SetDiffuse(Donut::vector4(1.0,0,0,1.0));
	scene->lights.push_back(lightSource2);

	Donut::TLight* lightSource3 = new Donut::TLight();
	lightSource3->SetPosition(Donut::vector3(120.0,25,0));
	lightSource3->SetDiffuse(Donut::vector4(0.0,1,0,1.0));
	scene->lights.push_back(lightSource3);

	Donut::TLight* lightSource4 = new Donut::TLight();
	lightSource4->SetPosition(Donut::vector3(200.0,30,-200));
	lightSource4->SetDiffuse(Donut::vector4(1,1,1,1.0));
	scene->lights.push_back(lightSource4);

	scene->root = new Donut::TNode();
	Donut::TShader shader("shaders/basetex/vertex.glsl", "shaders/basetex/geometry.glsl","shaders/basetex/fragment.glsl");
	Donut::TMesh* basePlane = Donut::CreatePlane(175, 200, shader);
	basePlane->AddTexture(Donut::ResourceManager::Instance().FetchTexture("data/textures/farmhouse.jpg"), "textureCmp");
	Donut::TSceneNode* nodePlane = new Donut::TSceneNode();
	nodePlane->Translate(Donut::vector3(150, -10, -175));
	nodePlane->AddDrawable(basePlane);
	scene->root->AttachChild(nodePlane);
	for (int i = 0; i< 10; i++)
	{
		for (int j = 0; j< 10; j++)
		{
			Donut::TMesh* teapot2 = Donut::CreateSugarInstance("Teapot");
			Donut::TSceneNode* node = new Donut::TSceneNode();
			node->Translate(Donut::vector3(30*j,0,-40*i));
			node->AddDrawable(teapot2);
			scene->root->AttachChild(node);
		}
	}

	Donut::TPipeline* renderingPipeline = Donut::GenerateGraphicPipeline(scene, newContext.width, newContext.lenght, Donut::TPipelineConfig::REALIST);
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
