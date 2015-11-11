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

#include <Render/Renderer.h>
#include <Input/InputHelper.h>
#include <Input/DefaultInputManager.h>
#include <Input/InputManager.h>
#include <graphics/factory.h>
#include <core/SceneNode.h>


int main()
{
	/*
	// Creating the rendering window
	Donut::TRenderer * window = new Donut::TRenderer();

	// Context info
	Donut::TGraphicsSettings newContext;
	newContext.windowName = "testOuline";
	newContext.width = 1280;
	newContext.lenght = 720;
	newContext.major = 4;
	newContext.minor = 1;
	window->CreateRenderWindow(newContext, 1);
	Donut::TShader rpShader("shaders/canvas/outVertex.glsl", "shaders/canvas/outFragment.glsl");
	window->SetShader(rpShader);
	window->Init();

	// Getting the camera
	Donut::TRenderPass* pass= window->GetPasses()[0];
	Donut::TNode* root= pass->GetRoot();
	Donut::Camera* camera = pass->GetCamera();
	Donut::TDefaultInputManager* inManager = static_cast<Donut::TDefaultInputManager*>(Donut::GetInputManager());
	inManager->FCamera = camera;
	camera->DefinePerspective(45.0,1280.0/720.0,1.0,500.0);
	
	Donut::TShader uniformShader("shaders/uniform/vertex.glsl", "shaders/uniform/fragment.glsl");
	Donut::TMesh* cube = CreateCube(5.0, uniformShader);
	Donut::TMesh* cube2 = CreateCube(2.5, uniformShader);

	Donut::TSceneNode* node1 = new Donut::TSceneNode();
	node1->Translate(Donut::vector3(10,0, -20));
	Donut::TSceneNode* node2 = new Donut::TSceneNode();
	node2->Translate(Donut::vector3(20,0, -20));
	node1->AddDrawable(cube);
	node2->AddDrawable(cube2);
	root->AttachChild(node1);
	root->AttachChild(node2);
	window->RegisterToDraw(cube);
	window->RegisterToDraw(cube2);

	
	while(window->IsRendering())
	{
		window->Draw();
		Donut::FarmEvents();
		inManager->Update();
	}
	window->UnRegisterToDraw(cube);
	window->UnRegisterToDraw(cube2);
	delete cube;
	delete cube2;

	delete window;
	*/
	return 0;

}
