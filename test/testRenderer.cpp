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
#include <Engine/Engine.h>
#include <graphics/gl_backend.h>
#include <base/platform.h>

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
