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

#include <iostream>
#include <Render/Renderer.h>
#include <Input/InputHelper.h>
#include <Input/DefaultInputManager.h>
#include <Input/InputManager.h>
#include <resource/sugarloader.h>
#include <Render/Representations/3D/Mesh.h>
#include <Render/Representations/3D/CubeR.h>
#include <core/SceneNode.h>


int main()
{
	Donut::TSugarLoader::Instance().Init("data");	

	// Creating the rendering window
	Donut::TRenderer * window = new Donut::TRenderer();

	// Context info
	Donut::TGraphicsSettings newContext;
	newContext.windowName = "testSSAO";
	window->CreateRenderWindow(newContext, 1);
	window->SetRenderType(Donut::FrameCanvasContent::GBUFFER);
	window->SetVertexShader("shaders/canvas/ssaoV.glsl");
	window->SetFragmentShader("shaders/canvas/ssaoF.glsl");
	window->Init();

	// Getting the camera
	Donut::TRenderPass* pass= window->GetPasses()[0];
	Donut::TNode* root= pass->GetRoot();
	Donut::Camera* camera = pass->GetCamera();
	pass->AddTexture("data/textures/random.jpg", "random");
	Donut::TDefaultInputManager* inManager = static_cast<Donut::TDefaultInputManager*>(Donut::GetInputManager());
	inManager->FCamera = camera;
	camera->DefinePerspective(45.0,1280.0/720.0,1.0,5000.0);
	camera->Translate(Donut::vector3(0.0,-4, 15));
	Donut::TDrawable* house = new Donut::TMesh(/*Donut::vector3(0,0,-40),*/"House");
	Donut::TSceneNode* node = new Donut::TSceneNode();
	node->AddDrawable(house);
	root->AttachChild(node);
	window->RegisterToDraw(house);

	Donut::TDrawable* lego = new Donut::TMesh(/*Donut::vector3(0,0.05,-40),*/"Lego");
	Donut::TSceneNode* legoNode = new Donut::TSceneNode();
	legoNode->AddDrawable(lego);
	root->AttachChild(legoNode);
	window->RegisterToDraw(lego);


	while(window->IsRendering())
	{
		window->Draw();
		Donut::FarmEvents();
		inManager->Update();
	}
	window->UnRegisterToDraw(house);
	delete house;
	delete window;
	return 0;

}
