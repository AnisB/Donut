// Library include
#include "identifier.h"

// External include
#include <string>
#include <sstream>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

namespace Donut
{
	RECIPE_GUID GetFileHash(const std::string& _filename)
	{
		char buffer[20];
		struct stat attrib;                
		stat(_filename.c_str(), &attrib);
   		strftime(buffer,20,"%x - %I_%M_%S", localtime(&(attrib.st_ctime)));
		return std::hash<std::string>()(std::string(buffer));
	}
}