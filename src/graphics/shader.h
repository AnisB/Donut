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

#ifndef GRAPHICS_SHADER_DONUT 
#define GRAPHICS_SHADER_DONUT


// Library includes
#include "common.h"

// STL includes
#include <vector>

 namespace Donut
 {
 	// Basic shader (this does mean that we do not replace the default gl pipeline)
	#define BASIC_SHADER "DEFAULT"

 	// Flags for shader compilation
 	#define VERTEX_FLAG 0x0001
 	#define TESS_CONTROL_FLAG 0x0002
 	#define TESS_EVAL_FLAG 0x0004
 	#define GEOMETRY_FLAG 0x0008
 	#define FRAGMENT_FLAG 0x0010
	
	class ShaderManager;

	struct TShader
	{
		friend class ShaderManager;
		TShader()
		{
			FIsTesselated = false;
			FProgramID = 0;
			FVertexShader = BASIC_SHADER;
			FTessControl = BASIC_SHADER;
			FTessEval = BASIC_SHADER;
			FGeometryShader = BASIC_SHADER;
			FFragmentShader = BASIC_SHADER;
			FActive = false;
		}

		TShader(const std::string& _vertex, const std::string& _fragment)
		{
			FIsTesselated = false;
			FProgramID =  0;
			FVertexShader = _vertex;
			FTessControl = BASIC_SHADER;
			FTessEval = BASIC_SHADER;
			FGeometryShader = BASIC_SHADER;
			FFragmentShader = _fragment;
			FActive = false;
		}
		TShader(const TShader& parShader)
		{
			FIsTesselated = parShader.FIsTesselated;
			FProgramID = parShader.FProgramID;
			FVertexShader = parShader.FVertexShader;
			FTessControl = parShader.FTessControl;
			FTessEval = parShader.FTessEval;
			FGeometryShader = parShader.FGeometryShader;
			FFragmentShader = parShader.FFragmentShader;
			FActive = parShader.FActive;
		}

		std::string FVertexShader;
		std::string FTessControl;
		std::string FTessEval;
		std::string FGeometryShader;
		std::string FFragmentShader;
		bool 		FIsTesselated;
		GLuint FProgramID;

		inline bool IsActive() {return FActive;}
private:
		bool FActive;

	};
 }

 #endif //GRAPHICS_SHADER_DONUT