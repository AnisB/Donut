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
#include <Render/Defines.h>
#include <unistd.h>


int main()
{
	Donut::TSugarLoader& modeltest = Donut::TSugarLoader::Instance();	
	modeltest.SetDirectory("data");
	modeltest.LoadSugars();
	// Creating the rendering window
	Donut::TRenderer * window = new Donut::TRenderer();

	// Context info
	Donut::TContextDetail newContext;
	newContext.windowName = "testGbuffer";
	newContext.width = 1280;
	newContext.lenght = 720;
	newContext.major = 4;
	newContext.minor = 1;
	window->CreateRenderWindow(newContext, 1);
	window->SetFragmentShader("shaders/test/gbufferVertex.glsl");
	window->SetFragmentShader("shaders/test/gbufferFragment.glsl");
	window->SetRenderType(Donut::FrameCanvasContent::GBUFFER);
	window->Init();

	// Getting the camera
	std::vector<Donut::TRenderPass*>& passes = window->GetPasses();
	Donut::Camera* camera = passes[0]->GetCamera();
	Donut::DefaultInputManager * inManager = new Donut::DefaultInputManager();
	Donut::SetInputManager(inManager);
	inManager->FCamera = camera;
	camera->DefinePerspective(45.0,1280.0/720.0,1.0,500.0);
	Donut::TDrawableObject* teapot = new Donut::TMesh(TVec3(0,0,-40),"Teapot");
	Donut::TDrawableObject* cube = new Donut::TCubeR(TVec3(5,0,-5),0.5);

	teapot->GenerateShader();
	teapot->Init();
	cube->GenerateShader();
	cube->Init();
	window->RegisterToDraw(teapot);
	window->RegisterToDraw(cube);
	
	while(window->IsRendering())
	{
		window->Draw();
		Donut::FarmEvents();
		inManager->Update(0.016);
	}
	window->UnRegisterToDraw(cube);
	window->UnRegisterToDraw(teapot);
	delete teapot;
	delete cube;

	delete window;
	return 0;

}
