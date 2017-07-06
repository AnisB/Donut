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

// donut include
#include "fileloader.h"
#include "base/security.h"

// STL include 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sstream>
#include <fstream>
#include <dirent.h>

#if LINUX | WIN32
#include <algorithm>
#endif

namespace donut
{
	void ReadFile( char const* fn, STRING_TYPE& _output) 
	{
		ASSERT_MSG(fn != NULL, "Empty file name to load");
		std::ifstream fileReader (fn);
		if (fileReader.is_open())
		{
			STRING_TYPE line;
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
	void ReadFile( char const* fn, std::vector<char>& _output) 
	{
		ASSERT_MSG(fn != NULL, "Empty file name to load");
		std::ifstream fileReader (fn);
		if (fileReader.is_open())
		{
			_output.insert(_output.end(),std::istreambuf_iterator<char>(fileReader), std::istreambuf_iterator<char>());
			_output.push_back('\0');
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

	void GetExtensionFileList(const STRING_TYPE& _directoryPath, const STRING_TYPE& _fileExtension, std::vector<STRING_TYPE>& _outContainer)
	{
        // Opening the directory
        DIR * directory;
        directory = opendir (_directoryPath.c_str());
        if (! directory) 
        {
#if __posix__
            ASSERT_FAIL_MSG("Error in directory: "<< _directoryPath<<" Error n°: "<< strerror (errno)); 
#elif WIN32
			char msg[20];
            ASSERT_FAIL_MSG("Error in directory: "<< _directoryPath<<" Error n°: "<< strerror_s (msg, errno));
#endif
        }

        int extensionSize = _fileExtension.size();

        // For each file in the directory
        while (1) 
        {
        	// If each new entry
            struct dirent* newEntry;
            newEntry = readdir (directory);
            if (! newEntry) 
            {
                break;
            }

            // Get its filename
            STRING_TYPE fileName(newEntry->d_name);
            // Reject non matching entries
            if((fileName=="..")|| (fileName==".") || fileName.size() < extensionSize)
            {
                continue;
            }

           	if( fileName.substr(fileName.size() - extensionSize, fileName.size())!= _fileExtension)
            {
                continue;
            }
            // OK this file is concerned we add it
            STRING_TYPE newFilename = _directoryPath;
            newFilename += "/";
            newFilename += fileName;
            _outContainer.push_back(newFilename);
        }
        if (closedir (directory)) 
        {
            ASSERT_FAIL_MSG("Error while closing directory: "<< _directoryPath); 
            return;
        }
	}
}




