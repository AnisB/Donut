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
#include "resource/shaderfilehandler.h"

// STL includes
#include <vector>

 namespace Donut
 {
 	// Basic shader (this does mean that we do not replace the default gl pipeline)
	#define BASIC_SHADER -1

 	// Flags for shader compilation
 	#define VERTEX_FLAG 0x0001
 	#define TESS_CONTROL_FLAG 0x0002
 	#define TESS_EVAL_FLAG 0x0004
 	#define GEOMETRY_FLAG 0x0008
 	#define FRAGMENT_FLAG 0x0010
	
	class ShaderManager;

	struct TShader
	{
		// Friends
		friend class ShaderManager;
		
		// Constructors
		TShader();
		TShader(const std::string& _vertex, const std::string& _fragment);
		TShader(const std::string& _vertex, const std::string& _geometry, const std::string& _fragment);
		TShader(const TShaderFileID& _vertex, const TShaderFileID& _fragment);
		TShader(const TShader& _shader);

		// Attributes
		TShaderFileID FVertexShader;
		TShaderFileID FTessControl;
		TShaderFileID FTessEval;
		TShaderFileID FGeometryShader;
		TShaderFileID FFragmentShader;
		bool 		FIsTesselated;
		GLuint FProgramID;

		inline bool IsActive() {return FActive;}

private:
		bool FActive;
	};

	inline bool operator==(const TShader& _shader1, const TShader& _shader2)
	{
		return (_shader1.FVertexShader == _shader2.FVertexShader) 
			&& (_shader1.FTessControl == _shader2.FTessControl)
			&& (_shader1.FTessEval == _shader2.FTessEval)
			&& (_shader1.FGeometryShader == _shader2.FGeometryShader)
			&& (_shader1.FFragmentShader == _shader2.FFragmentShader);
	}

	// Shader hashing class
	struct TShaderHasher
	{
		inline size_t operator()(const TShader& _shader)
		{
			size_t v0 = std::hash<TShaderFileID>()(_shader.FVertexShader);
			size_t v1 = std::hash<TShaderFileID>()(_shader.FTessControl);
			size_t v2 = std::hash<TShaderFileID>()(_shader.FTessEval);
			size_t v3 = std::hash<TShaderFileID>()(_shader.FGeometryShader);
			size_t v4 = std::hash<TShaderFileID>()(_shader.FFragmentShader);
			return v0 ^ (v1<<1) ^ (v2<<2) ^(v3<<3) ^ (v4<<4);
		}
	};
 }

 #endif //GRAPHICS_SHADER_DONUT