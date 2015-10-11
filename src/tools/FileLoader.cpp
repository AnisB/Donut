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

// Donut include
#include "fileloader.h"
#include <base/common.h>

// STL include 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sstream>
#include <fstream>

#if LINUX | WIN32
#include <algorithm>
#endif

namespace Donut
{
	bool BothAreSpaces(char lhs, char rhs) 
	{ 
		return (lhs == rhs) && (lhs == ' '); 
	}

	void readFile( char const* fn, std::string& _output) 
	{
		ASSERT_MSG(fn != NULL, "Empty file name to load");
		std::ifstream fileReader (fn);
		if (fileReader.is_open())
		{
			std::string line;
			while ( getline (fileReader, line) )
			{
				_output += line;
				_output += "\n";
			}
			fileReader.close();
		}
		else
		{
			ASSERT_FAIL_MSG("Failed could not be loaded "<<fn);
		}
	}

	bool WriteFile(char *fn, char *s) 
	{

		FILE *fp;
		bool status = false;

		if (fn != NULL) 
		{
			#if __posix__
			fp = fopen(fn,"w");
			#elif WIN32
			fopen_s(&fp,fn,"w");
			#endif
			if (fp != NULL) 
			{
				if (fwrite(s,sizeof(char),strlen(s),fp) == strlen(s))
					status = true;
				fclose(fp);
			}
		}
		return(status);
	}
	void split(const std::string& parString, char parSeparator, std::vector<std::string>& _out) 
	{
	    std::stringstream streamObj(parString);
	    std::string item;
	    while (std::getline(streamObj, item, parSeparator)) 
	    {
	        _out.push_back(item);
	    }
	}

	std::string removeMultSpace(const std::string& parString) 
	{
		std::string str = parString;
	    // Si string nulle on renvoie la string nulle

		std::string::iterator new_end = std::unique(str.begin(), str.end(), BothAreSpaces);
		str.erase(new_end, str.end());  
	    return str;
	}
}




