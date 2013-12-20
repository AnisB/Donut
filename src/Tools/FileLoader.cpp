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



#include "FileLoader.h"

#include "Base/Common.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sstream>

namespace Donut
{

	bool BothAreSpaces(char lhs, char rhs) { return (lhs == rhs) && (lhs == ' '); }

	char * LoadFile( char const* fn) 
	{
		FILE *fp;
		char *content = NULL;

		int count=0;

		if (fn != NULL) {
			fp = fopen(fn,"rt");

			if (fp != NULL) {
	      
	      fseek(fp, 0, SEEK_END);
	      count = ftell(fp);
	      rewind(fp);

				if (count > 0) {
					content = (char *)malloc(sizeof(char) * (count+1));
					count = fread(content,sizeof(char),count,fp);
					content[count] = '\0';
				}
				fclose(fp);
			}
		}
		CondAssertReleasePrint((content != NULL),fn);
		return content;
	}

	bool WriteFile(char *fn, char *s) {

		FILE *fp;
		bool status = false;

		if (fn != NULL) {
			fp = fopen(fn,"w");

			if (fp != NULL) {
				
				if (fwrite(s,sizeof(char),strlen(s),fp) == strlen(s))
					status = true;
				fclose(fp);
			}
		}
		return(status);
	}
	std::vector<std::string> split(const std::string& parString, char parSeparator, std::vector<std::string> &outStringTable) 
	{
	    std::stringstream streamObj(parString);
	    std::string item;
	    while (std::getline(streamObj, item, parSeparator)) 
	    {
	        outStringTable.push_back(item);
	    }
	    return outStringTable;
	}

	std::vector<std::string> split(const std::string& parString, char parSeparator)
	{
	    std::vector<std::string> stringTable;
	    split(parString, parSeparator, stringTable);
	    return stringTable;
	}

	std::string removeMultSpace(const std::string& parString) 
	{
		std::string str = parString;
	    // Si string nulle on renvoie la string nulle

		std::string::iterator new_end = std::unique(str.begin(), str.end(), BothAreSpaces);
		str.erase(new_end, str.end());  
	    return str;
	}

	int convertToInt(const std::string& parToConvert)
	{
		std::stringstream streamConverter;
		streamConverter<<parToConvert;
		int result;
		streamConverter>>result;
		return result;
	}
	float convertToFloat(const std::string& parToConvert)
	{
		std::stringstream streamConverter;
		streamConverter<<parToConvert;
		float result;
		streamConverter>>result;
		return result;
	}
}




