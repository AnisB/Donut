// Library include
#include "recipe/identifier.h"

// External include
#include <string>
#include <sstream>
#include <sys/types.h>
#include <sys/stat.h>
#if __posix__
#include <unistd.h>
#else
#include <time.h>
#endif

namespace donut
{
	RECIPE_GUID GetFileHash(const char* _filename)
	{
		char buffer[20];
		struct stat attrib;                
		stat(_filename, &attrib);
   		strftime(buffer,20,"%x - %I_%M_%S", localtime(&(attrib.st_ctime)));
		return std::hash<STRING_TYPE>()(STRING_TYPE(buffer));
	}
}