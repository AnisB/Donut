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
#include "tools/fileloader.h"
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

	bool path_is_file(const char *path)
	{
	    struct stat path_stat;
	    stat(path, &path_stat);
	    return S_ISREG(path_stat.st_mode) != 0;
	}

	void get_all_files_with_extension(const char* root_dir_path, const char* file_extension, std::vector<STRING_TYPE>& matching_files)
	{
        // Opening the directory
        DIR * directory;
        directory = opendir (root_dir_path);

        if (! directory) 
        {
            ASSERT_FAIL_MSG("Error in directory: "<< root_dir_path <<" Error n°: "<< strerror (errno)); 
        }

        uint32_t extensionSize = (uint32_t)strlen(file_extension);

        // For each entry in the directory
        while (1) 
        {
        	// If each new entry
            struct dirent* newEntry;
            newEntry = readdir (directory);
            if (! newEntry)
            {
            	// The entry is not valid, we done
                break;
            }

            // Get its filename
            STRING_TYPE entry_name(newEntry->d_name);

            // Reject dummy entries
            if((entry_name=="..")|| (entry_name=="."))
            {
                continue;
            }
            STRING_TYPE absolute_path = root_dir_path;
            absolute_path += "/";
            absolute_path += entry_name;

            // Check if the entry is a directory or not
            bool is_file = path_is_file(absolute_path.c_str());

            if(is_file)
            {
            	if( entry_name.size() < extensionSize || entry_name.substr(entry_name.size() - extensionSize, entry_name.size())!= file_extension)
	            {
	                continue;
	            }
	            // We find anice fella over here
            	matching_files.push_back(absolute_path);
            }
            else
            {
            	// We need to go recursive
            	get_all_files_with_extension(absolute_path.c_str(), file_extension, matching_files);
            }
        }
        if (closedir (directory)) 
        {
            ASSERT_FAIL_MSG("Error while closing directory: "<< root_dir_path);
            return;
        }
	}
}




