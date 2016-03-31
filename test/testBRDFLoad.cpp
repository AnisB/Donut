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

int main(int argc, char** argv)
{
	ASSERT(argc == 2);
	Donut::ResourceManager::Instance().Init("assets");	

	// Creating the rendering window
	Donut::TRenderer * window = new Donut::TRenderer();
	// Context info
	Donut::TGraphicsSettings newContext;
	newContext.windowName = "testSceneLoad";
	newContext.width = 1280;
	newContext.lenght = 720;
	newContext.major = 4;
	newContext.minor = 1;
	window->CreateRenderWindow(newContext);
	Donut::ResourceManager& resourcemanager = Donut::ResourceManager::Instance();
	resourcemanager.FetchBRDF(argv[1]);
	return 0;
}