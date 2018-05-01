
// Library includes
#include <graphics/pipeline.h>
#include <Render/Renderer.h>
#include <Input/helper.h>
#include <Input/DefaultInputManager.h>
#include <Input/InputManager.h>
#include <resource/resource_manager.h>
#include <graphics/factory.h>
#include <core/scenenode.h>
#include <gpu_backend/gl_backend.h>
#include <gpu_backend/gl_factory.h>

// Bento includes
#include <bento_math/vector3.h>
#include <bento_math/vector4.h>

int main(int argc, char** argv)
{
	if (argc != 3)
	{
	  return -1;
	}

	bool init_res = donut::ResourceManager::Instance().init(argv[1]);
	if (!init_res) return -1;

	// Creating the rendering window
	donut::TRenderer * window = new donut::TRenderer();
	// Context info
	donut::TGraphicSettings newContext = donut::gl::default_settings();
	newContext.window_name = "testFlourLoad";
	window->CreateRenderWindow(newContext);

	donut::TFlour* flour = donut::GenerateFlour(argv[2]);
	donut::TPipeline* renderingPipeline;
	renderingPipeline = donut::GenerateGraphicPipeline(flour, newContext.width, newContext.lenght);
	window->SetPipeline(renderingPipeline);
	window->Init();
	
	donut::Camera* camera = renderingPipeline->camera;
	donut::TDefaultInputManager* inManager = static_cast<donut::TDefaultInputManager*>(donut::input_manager());
	inManager->FCamera = camera;
	camera->DefinePerspective(45.0, newContext.width/(double)newContext.lenght,1.0,2000.0);
	
	while(window->IsRendering())
	{
		window->Draw();
		window->collect_inputs();
		inManager->Update();
	}

	delete window;
	return 0;
}