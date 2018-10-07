// Engine includes
#include <graphics/pipeline.h>
#include <Render/Renderer.h>
#include <Input/helper.h>
#include <Input/DefaultInputManager.h>
#include <Input/InputManager.h>
#include <resource/resource_manager.h>
#include <graphics/factory.h>
#include <core/scenenode.h>
#include <gpu_backend/gpu_backend.h>
#include <asset_compiler/compiler.h>

int main(int argc, char** argv)
{
	// Allocator used for this program
	bento::IAllocator& current_alloc = *bento::common_allocator();

	// Collect the arguments
	uint32_t num_args = argc;
	bento::Vector<bento::DynamicString> arg_array(current_alloc);
	arg_array.resize(num_args);
	for (uint32_t arg_idx = 0; arg_idx < num_args; ++arg_idx)
	{
		arg_array[arg_idx] = argv[arg_idx];
	}

	// Build the compiler options
	donut::TCompilerOptions options(current_alloc);
	donut::asset_compiler::build_from_args(options, arg_array);

	if (options._target_flour == "")
	{
		return -1;
	}

	// Initialize and fetch the target gpu api
	donut::initialize_gpu_backend(donut::RenderingBackEnd::OPENGL);
	const donut::GPUBackendAPI* targetBackend = donut::gpu_api(donut::RenderingBackEnd::OPENGL);
	assert_msg(targetBackend != nullptr, "Could not initialize rendering backend");

	// Initialize the resource manager with the rendering backend it should be using
	donut::ResourceManager::Instance().initialize(targetBackend);


	// Compile and store directly into the resource manager
	bool compilationResult = donut::asset_compiler::compile(options, donut::ResourceManager::Instance().asset_database());
	// Quit if the compilation failed
	if (!compilationResult) return -1;

	// Build the settings for this program
	donut::TGraphicSettings newContext = targetBackend->default_settings;
	newContext.window_name = "flour_loader";

	// Create the render window and initialize the backend context
	donut::TRenderer window;
	window.CreateRenderWindow(newContext, targetBackend);

	// Load and instanciate the target flour
	donut::TFlour* flour = donut::GenerateFlour(options._target_flour.c_str());
	assert_msg(flour != nullptr, "Could not fetch flour");

	// Load and instanciate the rendering pipeline
	donut::TPipeline* renderingPipeline;
	renderingPipeline = donut::GenerateGraphicPipeline(flour, newContext.width, newContext.lenght, targetBackend);
	assert_msg(flour != nullptr, "Could not create renderingPipeline");

	window.SetPipeline(renderingPipeline);
	window.Init();
	
	donut::Camera* camera = renderingPipeline->camera;
	donut::TDefaultInputManager* inManager = static_cast<donut::TDefaultInputManager*>(donut::input_manager());
	inManager->FCamera = camera;
	inManager->init(targetBackend);
	camera->DefinePerspective(45.0f, newContext.width/(float)newContext.lenght, 0.01f, 1000.0f);
	
	while(window.IsRendering())
	{
		window.Draw();
		window.collect_inputs();
		inManager->Update();
	}

	return 0;
}