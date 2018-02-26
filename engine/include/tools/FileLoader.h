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
#ifndef DONUT_FILE_LOADER
#define DONUT_FILE_LOADER

// LIbrary includes
#include "resource/egg.h"
#include "butter/vector3.h"
#include "butter/vector4.h"
#include "butter/matrix4.h"
#include "base/stringhelper.h"

// Std includes
#include <vector>
#include <string>
#include <sstream>

namespace donut
{
	//Loads file , free with mallpoc
	void ReadFile(char const* fn, STRING_TYPE& _output);
	void ReadFile(char const* fn, std::vector<char>& _output);
	// Writes s in f
	bool WriteFile(char *fn, char *s);

	template<typename T>
	void stringConvertArray(const STRING_TYPE& _param, std::vector<T>& _values)
	{
		std::vector<STRING_TYPE> stringValues;
		split(_param, ' ',stringValues);
		for(const auto& val : stringValues)
		{
			_values.push_back(convert_from_string<T>(val));
		}
	}

	// This function returns the list of file of a given extension in the ouputcontainer
	void get_all_files_with_extension(const char* root_dir_path, const char* file_extension, std::vector<STRING_TYPE>& _outContainer);
}

#endif // FILE_LOADER