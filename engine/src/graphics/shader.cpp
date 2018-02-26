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
#include "graphics/shader.h"

namespace donut
{
	// Default Constructor
	TShader::TShader()
	: FIsTesselated(false)
	, FProgramID(0)
	, FVertexShader(BASIC_SHADER)
	, FTessControl(BASIC_SHADER)
	, FTessEval(BASIC_SHADER)
	, FGeometryShader(BASIC_SHADER)
	, FFragmentShader(BASIC_SHADER)
	, FActive(false)
	{
	}

	// This should go into a factory
	TShader::TShader(const STRING_TYPE& _vertex, const STRING_TYPE& _fragment)
	: FIsTesselated(false)
	, FProgramID(0)
	, FTessControl(BASIC_SHADER)
	, FTessEval(BASIC_SHADER)
	, FGeometryShader(BASIC_SHADER)
	, FActive(false)
	{
		TShaderFileHandler& shaderFileHandler = TShaderFileHandler::Instance();
		FVertexShader = shaderFileHandler.RegisterShaderFile(_vertex);
		FFragmentShader =  shaderFileHandler.RegisterShaderFile(_fragment);
	}

	TShader::TShader(const STRING_TYPE& _vertex, const STRING_TYPE& _geometry, const STRING_TYPE& _fragment)
	: FIsTesselated(false)
	, FProgramID(0)
	, FTessControl(BASIC_SHADER)
	, FTessEval(BASIC_SHADER)
	, FActive(false)
	{
		TShaderFileHandler& shaderFileHandler = TShaderFileHandler::Instance();
		FVertexShader = shaderFileHandler.RegisterShaderFile(_vertex);
		FGeometryShader =  shaderFileHandler.RegisterShaderFile(_geometry);
		FFragmentShader =  shaderFileHandler.RegisterShaderFile(_fragment);
	}


	// This should go into a factory
	TShader::TShader(const TShaderFileID& _vertex, const TShaderFileID& _fragment)
	: FIsTesselated(false)
	, FProgramID(0)
	, FVertexShader(_vertex)
	, FTessControl(BASIC_SHADER)
	, FTessEval(BASIC_SHADER)
	, FGeometryShader(BASIC_SHADER)
	, FFragmentShader(_fragment)
	, FActive(false)
	{
	}

	// Copy constructor
	TShader::TShader(const TShader& _shader)
	: FIsTesselated(_shader.FIsTesselated)
	, FProgramID(_shader.FProgramID)
	, FVertexShader(_shader.FVertexShader)
	, FTessControl(_shader.FTessControl)
	, FTessEval(_shader.FTessEval)
	, FGeometryShader(_shader.FGeometryShader)
	, FFragmentShader(_shader.FFragmentShader)
	, FActive(_shader.FActive)
	{
	}

}
