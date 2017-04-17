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
#ifndef GRAPHICS_SETTINGS_DONUT
#define GRAPHICS_SETTINGS_DONUT

#include <string>
	
namespace Donut
{
    // Default context data
    #define DEFAULT_WIDTH 1280 
	#define DEFAULT_LENGHT 720
	#define DEFAULT_NAME "Donut"
	#define DEFAULT_FULLSCREEN false

	struct TGraphicsSettings
	{
		std::string window_name;
		uint32_t width;
		uint32_t lenght;
		bool fullScreen;
		uint64_t data[5];

		TGraphicsSettings()
		{
			window_name = DEFAULT_NAME;
			width = DEFAULT_WIDTH;
			lenght = DEFAULT_LENGHT;
			fullScreen = DEFAULT_FULLSCREEN;
		}
	};
}	
#endif