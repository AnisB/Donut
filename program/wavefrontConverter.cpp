
// Bento includes
#include <bento_base/security.h>

// Library includes
#include "tools/GeometryConverters.h"

// STL includes
#include <fstream>
int main(int argc, char** argv)
{
	assert_msg(argc == 3, "Wrong number of parameters, you should specify the input an output files.");
	STRING_TYPE inputFile(argv[1]);
	STRING_TYPE outputFile(argv[2]);
	donut::ConvertWavefrontToEgg(inputFile, outputFile);
	return 0;
}