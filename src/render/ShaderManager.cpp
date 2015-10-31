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

 #include "ShaderManager.h"
 #include <Tools/FileLoader.h>
 #include <Base/Common.h>
 #include <Render/Defines.h>
 #include <render/helper.h>
 #include <stdlib.h>
 #include "Base/Macro.h"
 #include "render/common.h"
 
namespace Donut 
{
	void CheckShader(GLuint parShaderID, const std::string& parShadePath)
	{
	    GLint Result = GL_FALSE;
	    int InfoLogLength;
	    
	    glGetShaderiv(parShaderID, GL_COMPILE_STATUS, &Result);
	    glGetShaderiv(parShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);

	    if(InfoLogLength>1)
	    {
	        char* errorMessage = new char[InfoLogLength];
	        glGetShaderInfoLog(parShaderID, InfoLogLength, NULL, errorMessage);
	        RENDER_DEBUG( "Shader error:"<<parShadePath<<" "<<parShaderID);
	        RENDER_ERROR( errorMessage );
			delete [] errorMessage;
	    }
	}


	bool CheckProgram(GLuint parProgramID)
	{
	    GLint Result = GL_FALSE;
	    int InfoLogLength;
	    
	    glGetProgramiv(parProgramID, GL_LINK_STATUS, &Result);
	    glGetProgramiv(parProgramID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	    if(InfoLogLength>1)
	    {   
	        char* errorMessage = new char[InfoLogLength];
	        glGetProgramInfoLog(parProgramID, InfoLogLength, NULL, errorMessage);
	        RENDER_ERROR("Program linking error: "<<std::endl<<errorMessage );
			delete [] errorMessage;
	    }
	    return true;
	}

	ShaderManager::ShaderManager()
	{
	}

	ShaderManager::~ShaderManager()
	{
		
	}

	bool ShaderManager::CreateShader(TShader& parShader)
	{
		RENDER_DEBUG("Creating shader kernel");
		GLuint programID;
		GLuint vertexShader;
		GLuint tessControlShader;
		GLuint tessEvalShader;
		GLuint geometryShader;
		GLuint fragmentShader;

		programID = glCreateProgram();

		if(parShader.FVertexShader!=BASIC_SHADER)
		{
			std::string vsFile;
			vertexShader = glCreateShader(GL_VERTEX_SHADER);
			readFile(parShader.FVertexShader.c_str(),vsFile);
			const char * vsFile_ptr = vsFile.c_str();
			glShaderSource(vertexShader, 1, (const char **)&vsFile_ptr, NULL);
			glCompileShader(vertexShader);
			CheckShader(vertexShader, parShader.FVertexShader);
			glAttachShader(programID,vertexShader);			

		}
		if(parShader.FTessControl!=BASIC_SHADER)
		{
			std::string tcsFile;
			tessControlShader = glCreateShader(GL_TESS_CONTROL_SHADER);
			readFile(parShader.FTessControl.c_str(), tcsFile);
			const char * tcsFile_ptr = tcsFile.c_str();
			glShaderSource(tessControlShader, 1, (const char **)&tcsFile_ptr, NULL);
			glCompileShader(tessControlShader);
			CheckShader(tessControlShader, parShader.FTessControl);
			glAttachShader(programID,tessControlShader);
		}

		if(parShader.FTessEval!=BASIC_SHADER)
		{
			std::string tesFile;
			tessEvalShader = glCreateShader(GL_TESS_EVALUATION_SHADER);
			readFile(parShader.FTessEval.c_str(), tesFile);
			const char * tesFile_ptr = tesFile.c_str();
			glShaderSource(tessEvalShader, 1, (const char **)&tesFile_ptr, NULL);
			glCompileShader(tessEvalShader);
			CheckShader(tessEvalShader, parShader.FTessEval);
			glAttachShader(programID,tessEvalShader);
		}

		if(parShader.FGeometryShader!=BASIC_SHADER)
		{
			std::string gsFile;
			geometryShader = glCreateShader(GL_GEOMETRY_SHADER);
			readFile(parShader.FGeometryShader.c_str(), gsFile);
			const char * gsFile_ptr = gsFile.c_str();
			glShaderSource(geometryShader, 1, (const char **)&gsFile_ptr, NULL);
			glCompileShader(geometryShader);
			CheckShader(geometryShader, parShader.FGeometryShader);
			glAttachShader(programID,geometryShader);
		}
		if(parShader.FFragmentShader!=BASIC_SHADER)
		{
			std::string fsFile;
			fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
			readFile(parShader.FFragmentShader.c_str(), fsFile);
			const char * fsFile_ptr = fsFile.c_str();
			glShaderSource(fragmentShader, 1, (const char **)&fsFile_ptr, NULL);
			glCompileShader(fragmentShader);
			CheckShader(fragmentShader, parShader.FFragmentShader);
			glAttachShader(programID,fragmentShader);
		}
		glLinkProgram(programID);
		if(CheckProgram(programID))
		{
			parShader.FProgramID = programID;
			parShader.FActive = true;
			FPrograms.push_back(parShader);
			RENDER_DEBUG("Shader created");
			return true;
		}
		else
		{
			ASSERT_FAIL_MSG_NO_RELEASE("Shader creation failed.");
			return false;
		}
	}

	void ShaderManager::EnableShader(const TShader& parProgram)
	{
		ASSERT_NO_RELEASE(parProgram.FActive);
		glUseProgram(parProgram.FProgramID);
	}

	void ShaderManager::DisableShader()
	{
		glUseProgram(0);
	}


	// Injections
	void ShaderManager::InjectVec3(const TShader& parProgram, const Vector3& parValue, const std::string& parName)
	{
	    glUniform3f(glGetUniformLocation(parProgram.FProgramID, parName.c_str()), parValue.x, parValue.y, parValue.z);
	}
	void ShaderManager::InjectVec4(const TShader& parProgram, const Vector4& parValue, const std::string& parName)
	{
	    glUniform4f(glGetUniformLocation(parProgram.FProgramID, parName.c_str()), parValue.x, parValue.y, parValue.z, parValue.w);
	}
	void ShaderManager::InjectInt(const TShader& parProgram, int parValue, const std::string& parName)
	{
		GLuint location = glGetUniformLocation(parProgram.FProgramID, parName.c_str());
	    glUniform1i(location, parValue);
	}
	void ShaderManager::InjectFloat(const TShader& parProgram, float parValue, const std::string& parName)
	{
	    glUniform1f( glGetUniformLocation(parProgram.FProgramID, parName.c_str()), parValue);
	}
	void ShaderManager::InjectMat4(const TShader& parProgram, const Matrix4& parValue, const std::string& parName)
	{
		float mat[16];
		ToTable(parValue, &mat[0]);
	    glUniformMatrix4fv(glGetUniformLocation(parProgram.FProgramID, parName.c_str()),1,true, mat);

	}
	void ShaderManager::InjectTex(const TShader& parProgram, size_t parIndexTex, const std::string& parName, GLuint parOffset)
	{
	   	glActiveTexture(GL_TEXTURE0+parOffset);
	    glBindTexture(GL_TEXTURE_2D, parIndexTex);
	    GLint texRef = glGetUniformLocation(parProgram.FProgramID, parName.c_str());
	    glUniform1i(texRef, 0+parOffset);
	}

	void ShaderManager::InjectCubeMap(const TShader& parProgram, size_t parIndexTex, const std::string& parName, GLuint parOffset)
	{
	   	glActiveTexture(GL_TEXTURE0+parOffset);
	    glBindTexture(GL_TEXTURE_CUBE_MAP, parIndexTex);
	    GLint texRef = glGetUniformLocation(parProgram.FProgramID, parName.c_str());
	    glUniform1i(texRef, 0+parOffset);
	}	

	void ShaderManager::BindTex(GLuint parIndexTex, GLuint parOffset)
	{
   		glActiveTexture(GL_TEXTURE0+parOffset);
	    glBindTexture(GL_TEXTURE_2D, parIndexTex);	
	}

	void ShaderManager::BindCubeMap(GLuint parIndexTex, GLuint parOffset)
	{
   		glActiveTexture(GL_TEXTURE0+parOffset);
	    glBindTexture(GL_TEXTURE_CUBE_MAP, parIndexTex);		
	}

	void ShaderManager::PreDrawSugarData(const TSugar&  parSugar)
	{
		foreach_macro(tex,parSugar.textures)
		{
			ShaderManager::Instance().BindTex(tex->texID, tex->index);
		}
	}

}
