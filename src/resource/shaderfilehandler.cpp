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

// Library includes
#include "shaderfilehandler.h"
#include "base\macro.h"
#include "base\security.h"

namespace Donut
{
	static TShaderFileID s_shaderCounter = 0;
	// Init and uninit
	TShaderFileHandler::TShaderFileHandler()
	{
		// Nothing to do
	}
		
	TShaderFileHandler::~TShaderFileHandler()
	{
		// Nothing to do
	}

	// Methods
	TShaderFileID TShaderFileHandler::RegisterShaderFile(const std::string& _shaderFile)
	{
		tryget(result, m_shaderKeys, _shaderFile);
		if(result == m_shaderKeys.end())
		{
			m_shaderKeys[_shaderFile] = s_shaderCounter;
			m_inverseShaderKeys[s_shaderCounter] = _shaderFile;
			return s_shaderCounter++; // The ++ operator returns a copy pre-incrementation
		}
		else
		{
			return result->second;
		}
	}

	const std::string& TShaderFileHandler::GetShaderFile(const TShaderFileID& _shaderID)
	{
		tryget(result, m_inverseShaderKeys, _shaderID);
		if(result == m_inverseShaderKeys.end())
		{
			ASSERT_MSG(result != m_inverseShaderKeys.end(), "Shader "<<_shaderID<<" was required but never registered");
		}
		return result->second;
	}

	bool TShaderFileHandler::IsRegistered(const std::string& _shaderFile)
	{
		tryget(result, m_shaderKeys, _shaderFile);
		return (result != m_shaderKeys.end());
	}
}