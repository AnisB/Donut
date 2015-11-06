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
#include "base/common.h"
#include "resource/resourcemanager.h"
#include "tools/fileloader.h"

// STL includes
#include <fstream>
int main(int argc, char** argv)
{
	ASSERT_MSG(argc == 3, "Wrong number of parameters, you should specify the input an output files.");
	std::string inputFile(argv[1]);
	std::string outputFile(argv[2]);
	GENERAL_INFO("Inputfile is "<<inputFile<<" Output file will be "<<outputFile);
	Donut::TGeometryContainer* geo = Donut::ResourceManager::Instance().ReadWavefront(argv[1]);
	GENERAL_INFO(inputFile<<" is in memory, outputing it into "<<outputFile);
 	std::ofstream outputStream;
    outputStream.open (outputFile , std::ios::out | std::ios::binary);
    outputStream << geo;
    outputStream.close();
	GENERAL_INFO("Done");
	return 0;
}