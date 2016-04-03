// Library include
#include "flourdescriptor.h"
#include "tools/xmlhelpers.h"
#include "tools/fileloader.h"

// External includes
#include "rapidxml.hpp"
namespace Donut
{
	void ParseFlourFile(const std::string& _fileName, TFlourDescriptor& _output)
	{
		// Registering the file name
		_output.file = _fileName;

        // reading the text file
        std::vector<char> buffer;
        ReadFile(_fileName.c_str(), buffer);

        _output.file = _fileName;
        // compute the id
        _output.id = GenerateGUID(&buffer[0]);
	}
}