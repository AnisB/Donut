
#include <iostream>
#include <gpu_backend\gl_backend.h>
#include <bento_base/platform.h>

using namespace donut;
int main()
{
	TEngine * engine = new TEngine();

	// Context info
	TGraphicsSettings newContext = GL::default_settings();
	newContext.window_name = "testRenderer";

	// Lanching the test
	engine->LaunchRendering(newContext);
	SLEEP_FUNCTION(1);
	engine->PauseRendering();
	SLEEP_FUNCTION(1);
	engine->ResumeRendering();
	SLEEP_FUNCTION(1);
	engine->StopRendering();
	SLEEP_FUNCTION(1);
	delete engine;
	return 0;

}
