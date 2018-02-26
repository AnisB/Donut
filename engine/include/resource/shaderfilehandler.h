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

#ifndef SHADER_FILE_HANDLER_RESOURCE_DONUT 
#define SHADER_FILE_HANDLER_RESOURCE_DONUT

// Library includes
#include "base/Singleton.h"
#include "base/stringhelper.h"

// STL includes
#include <unordered_map>
#include <string>

namespace donut
{
	// Referenced but unexisting shader
	#define NON_DEFINED_SHADER -2
	// ShaderFile ID
	typedef int TShaderFileID;

	class TShaderFileHandler : public Singleton<TShaderFileHandler>
	{
	public:
		// Init and uninit
		TShaderFileHandler();
		~TShaderFileHandler();

		// Methods
		TShaderFileID RegisterShaderFile(const STRING_TYPE& _shaderFile);
		const STRING_TYPE& GetShaderFile(const TShaderFileID& _shaderFile);
		bool IsRegistered(const STRING_TYPE& _shaderFile);

	protected:
		std::unordered_map<STRING_TYPE, TShaderFileID, std::hash<STRING_TYPE>> m_shaderKeys;
		std::unordered_map<TShaderFileID, STRING_TYPE> m_inverseShaderKeys;
	};
}
#endif // SHADER_FILE_HANDLER_RESOURCE_DONUT