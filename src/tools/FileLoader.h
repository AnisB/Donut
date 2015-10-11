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

// Std includes
#include <vector>
#include <string>
#include <sstream>

namespace Donut
{
	//Loads file , free with mallpoc
	void readFile(char const* fn, std::string& _output);
	// Writes s in f
	bool WriteFile(char *fn, char *s);
	// Splits parstring with parSeparator
	void split(const std::string& parString, char parSeparator, std::vector<std::string>& _out);
	// removes multiple spaces in a string
	std::string removeMultSpace(const std::string& parString); 

	// Converters from string
	template<typename T>
	T stringConvert(const std::string& _param)
	{
		std::stringstream streamConverter;
		streamConverter<<_param;
		T result;
		streamConverter>>result;
		return result;
	}
}

#endif // FILE_LOADER