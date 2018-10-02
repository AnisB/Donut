// Engine includes
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
#include <asset_compiler/compiler.h>

int main(int argc, char** argv)
{
	// Allocator used for this program
	bento::IAllocator& current_alloc = *bento::common_allocator();

	// Collect the arguments
	bento::Vector<bento::DynamicString> arg_array(current_alloc);
	arg_array.resize(argc);
	for (uint32_t arg_idx = 0; arg_idx < argc; ++arg_idx)
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

	// Compile and store directly into the resource manager
	bool compilationResult = donut::asset_compiler::compile(options, donut::ResourceManager::Instance().asset_database());
	// Quit if the compilation failed
	if (!compilationResult) return -1;

	// Initialize and request the target GPU backend API

	// Creating the rendering window
	donut::TRenderer window;

	// Build the settings for this program
	donut::TGraphicSettings newContext = donut::gl::default_settings();
	newContext.window_name = "flour_loader";

	// Initialize and fetch the target gpu api
	donut::initialize_gpu_backend(newContext.backend);
	const donut::GPUBackendAPI* targetBackend = donut::gpu_api(newContext.backend);
	window.CreateRenderWindow(newContext, targetBackend);

	donut::TFlour* flour = donut::GenerateFlour(options._target_flour.c_str());
	assert_msg(flour != nullptr, "Could not fetch flour");

	donut::TPipeline* renderingPipeline;
	renderingPipeline = donut::GenerateGraphicPipeline(flour, newContext.width, newContext.lenght, targetBackend);
	assert_msg(flour != nullptr, "Could not create renderingPipeline");

	window.SetPipeline(renderingPipeline);
	window.Init();
	
	donut::Camera* camera = renderingPipeline->camera;
	donut::TDefaultInputManager* inManager = static_cast<donut::TDefaultInputManager*>(donut::input_manager());
	inManager->FCamera = camera;
	inManager->init(targetBackend);
	camera->DefinePerspective(45.0, newContext.width/(double)newContext.lenght, 0.01f, 1000.0f);
	
	while(window.IsRendering())
	{
		window.Draw();
		window.collect_inputs();
		inManager->Update();
	}

	return 0;
}