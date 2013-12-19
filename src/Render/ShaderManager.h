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
 #ifndef  SHADER_MANAGER_DONUT 
 #define SHADER_MANAGER_DONUT



 #include "Defines.h"
 #include <base/singleton.h>
 #include <Math/Vector3.h>
 #include <Math/Matrix4.h>
 #include <list>

 namespace Donut
 {

 	struct TShader
 	{
 		TShader(GLuint parID, const std::string& parVShader,const std::string& parFShader)
 		{
 			FProgramID = parID;
 			FVertexShader = parVShader;
 			FFragmentShader = parFShader;
 			FActive = false;
 		}
		TShader(const TShader& parShader)
 		{
 			FProgramID = parShader.FProgramID;
 			FVertexShader = parShader.FVertexShader;
 			FFragmentShader = parShader.FFragmentShader;
 			FActive = parShader.FActive;
 		}

 		std::string FVertexShader;
 		std::string FFragmentShader;

 		bool FActive;
 		GLuint FProgramID;
 	};

 	class ShaderManager : public Singleton<ShaderManager>
 	{

 	public:
 		ShaderManager();
 		~ShaderManager();

 		TShader CreateShader(const std::string& parVertexShader, const std::string& parFragmentShader);

 		void EnableShader(const TShader& parProgram);
 		void DisableShader( );

 		// Injections
		void InjectInt(const TShader& parProgram, int parValue, const std::string& parName);
		
		void InjectVec3(const TShader& parProgram, const Vector3& parValue, const std::string& parName);

		void InjectMat4(const TShader& parProgram, const Matrix4& parValue, const std::string& parName);

		void InjectTex(const TShader& parProgram, size_t parIndexTex, const std::string& parName, GLuint parOffset);


 	private:
 		std::list<TShader> FPrograms;
 		TShader FBasicPipeline;

 	};
 }

 #endif //SHADER_MANAGER_DONUT