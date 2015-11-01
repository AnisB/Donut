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

#ifndef SHADER_MANAGER_DONUT 
#define SHADER_MANAGER_DONUT


// Library includes
#include "shader.h"

#include "base/singleton.h"
#include "butter/Vector3.h"
#include "butter/Matrix4.h"


// STL includes
#include <vector>

namespace Donut
{
 	class ShaderManager : public Singleton<ShaderManager>
 	{

 	public:
 		// Init && uninit
 		ShaderManager();
 		~ShaderManager();

 		// Creates a shader in GPU memory
 		bool CreateShader(TShader& parShader);

 		// Enables and disables a shader
 		void EnableShader(const TShader& parProgram);
 		void DisableShader( );

 		// Data injection
		void InjectInt(const TShader& parProgram, int parValue, const std::string& parName);
		void InjectFloat(const TShader& parProgram, float parValue, const std::string& parName);
		void InjectVec3(const TShader& parProgram, const Vector3& parValue, const std::string& parName);
		void InjectVec4(const TShader& parProgram, const Vector4& parValue, const std::string& parName);
		void InjectMat4(const TShader& parProgram, const Matrix4& parValue, const std::string& parName);
		
		// Texture binding/unbinding functions
		void BindTex(GLuint _texID, GLuint parOffset);
		void BindCubeMap(GLuint _texID, GLuint parOffset);
		void UnbindTex(GLuint parOffset);
		void UnbindCubeMap(GLuint parOffset);

		// Texture injection function
		void InjectTex(const TShader& parProgram, GLuint _texID, const std::string& parName, GLuint parOffset);
		void InjectCubeMap(const TShader& parProgram, GLuint _texID, const std::string& parName, GLuint parOffset);
 	private:
 		std::vector<TShader> FPrograms;
 	};
 }

 #endif //SHADER_MANAGER_DONUT