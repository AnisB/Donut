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

// Library includes
#include "tools/GeometryConverters.h"
#include "base/security.h"
#include "base/log.h"

// STL includes
#include <fstream>
int main(int argc, char** argv)
{
	ASSERT_MSG(argc == 3, "Wrong number of parameters, you should specify the input an output files.");
	STRING_TYPE inputFile(argv[1]);
	STRING_TYPE outputFile(argv[2]);
	PRINT_INFO("Conversion", "Inputfile is "<<inputFile<<" Output file will be "<<outputFile);
	donut::ConvertWavefrontToEgg(inputFile, outputFile);
	PRINT_INFO("Conversion","Conversion done");
	return 0;
}