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

#include <string.h>
	
namespace Donut
{
    // Default context data
    #define DEFAULT_MAJOR_VERSION 4
    #define DEFAULT_MINOR_VERSION 1
    #define DEFAULT_WINDOW_NAME 720
    #define DEFAULT_WIDTH 1280 
	#define DEFAULT_LENGHT 720
	#define DEFAULT_NAME "Donut"
	#define DEFAULT_FULLSCREEN false

	struct TGraphicsSettings
	{
		std::string windowName;
		int width;
		int lenght;
		int major;
		int minor;
		bool fullScreen;

		TGraphicsSettings()
		{
			windowName = DEFAULT_NAME;
			width = DEFAULT_WIDTH;
			lenght = DEFAULT_LENGHT;
			major = DEFAULT_MAJOR_VERSION;
			minor = DEFAULT_MINOR_VERSION;
			fullScreen = DEFAULT_FULLSCREEN;
		}
	};
}	