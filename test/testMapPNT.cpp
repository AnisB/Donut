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
#include <Render/Representations/3D/CubeR.h>
#include <core/SceneNode.h>


int main()
{
	// Creating the rendering window
	Donut::TRenderer * window = new Donut::TRenderer();

	// Context info
	Donut::TGraphicsSettings newContext;
	newContext.windowName = "testDisplay";
	newContext.width = 1280;
	newContext.lenght = 720;
	newContext.major = 4;
	newContext.minor = 1;
	window->CreateRenderWindow(newContext, 1);
	window->Init();

	// Getting the camera
	Donut::TRenderPass* pass= window->GetPasses()[0];
	Donut::TNode* root= pass->GetRoot();
	Donut::Camera* camera = pass->GetCamera();
	Donut::TDefaultInputManager* inManager = static_cast<Donut::TDefaultInputManager*>(Donut::GetInputManager());
	inManager->FCamera = camera;
	camera->DefinePerspective(45.0,1280.0/720.0,1.0,500.0);
	
	Donut::TShader shader;
	shader.FVertexShader = "shaders/test/testVertexPNT.glsl";
	shader.FFragmentShader = "shaders/test/testFragmentPNT.glsl";
	Donut::TCubeR* cube = new Donut::TCubeR(0.5,shader);
	Donut::TCubeR* cube2 = new Donut::TCubeR(1.0,shader);


	Donut::TSceneNode* node = new Donut::TSceneNode();
	node->AddDrawable(cube);
	node->AddDrawable(cube2);
	root->AddChild(node);
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
	return 0;

}
