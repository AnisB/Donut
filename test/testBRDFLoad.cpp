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
#include <resource/sugarloader.h>
#include <resource/resourcemanager.h>
#include <graphics/gl_backend.h>

int main(int argc, char** argv)
{
	ASSERT(argc == 2);
	donut::ResourceManager::Instance().Init("assets");	

	// Creating the rendering window
	donut::TRenderer * window = new donut::TRenderer();
	// Context info
	donut::TGraphicsSettings newContext = donut::GL::default_settings();
	newContext.window_name = "testBRDFLoad";
	window->CreateRenderWindow(newContext);
	donut::ResourceManager& resourcemanager = donut::ResourceManager::Instance();
	resourcemanager.FetchBRDF(argv[1]);
	return 0;
}