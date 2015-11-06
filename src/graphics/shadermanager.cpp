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
#include "shadermanager.h"
#include "base/common.h"
#include "graphics/common.h"
#include "base/macro.h"

#include "tools/fileloader.h"

// STL includes
#include <stdlib.h>

namespace Donut 
{
	void CheckShader(GLuint _shaderID, const std::string& _shaderFileName)
	{
		// flags
	    GLint result = GL_FALSE;
	    int infoLogLength = 0;

	    // Fetching the compulation results
	    glGetShaderiv(_shaderID, GL_COMPILE_STATUS, &result);
	    glGetShaderiv(_shaderID, GL_INFO_LOG_LENGTH, &infoLogLength);

	    // Failed?
	    if(infoLogLength > 1)
	    {
	    	// OK lets get the error message
	        char* errorMessage = new char[infoLogLength];
	        glGetShaderInfoLog(_shaderID, infoLogLength, NULL, errorMessage);
	        GRAPHICS_ERROR( "Shader error:"<<_shaderFileName<<" "<<_shaderID);
	        GRAPHICS_ERROR( errorMessage );
			delete [] errorMessage;
	    }
	}

	bool CheckProgram(GLuint _programID)
	{
		// flags
	    GLint result = GL_FALSE;
	    int infoLogLength = 0;
	    
	    // Fetching the link result
	    glGetProgramiv(_programID, GL_LINK_STATUS, &result);
	    glGetProgramiv(_programID, GL_INFO_LOG_LENGTH, &infoLogLength);

	    //Failed?
	    if(infoLogLength > 1)
	    {   
	    	// Ok, lets get the error message
	        char* errorMessage = new char[infoLogLength];
	        glGetProgramInfoLog(_programID, infoLogLength, NULL, errorMessage);
	        GRAPHICS_ERROR("Program linking error: "<< _programID<<std::endl<<errorMessage );
			delete [] errorMessage;
			return false;
	    }
	    return true;
	}

	ShaderManager::ShaderManager()
	{

	}

	ShaderManager::~ShaderManager()
	{
		// Here we should delete all the shaders that where created
		foreach_macro(shader, FPrograms)
		{
			glDeleteProgram(shader->FProgramID);
		}
	}

	bool ShaderManager::CreateShader(TShader& parShader)
	{
		GRAPHICS_DEBUG("Creating shader kernel");
		GLuint programID = 0;
		GLuint vertexShader = 0;
		GLuint tessControlShader = 0;
		GLuint tessEvalShader = 0;
		GLuint geometryShader = 0;
		GLuint fragmentShader = 0;

		programID = glCreateProgram();
		char shaderFlags = 0;
		if(parShader.FVertexShader!=BASIC_SHADER)
		{
			std::string vsFile;
			vertexShader = glCreateShader(GL_VERTEX_SHADER);
			ReadFile(parShader.FVertexShader.c_str(),vsFile);
			const char * vsFile_ptr = vsFile.c_str();
			glShaderSource(vertexShader, 1, (const char **)&vsFile_ptr, NULL);
			glCompileShader(vertexShader);
			CheckShader(vertexShader, parShader.FVertexShader);
			glAttachShader(programID, vertexShader);
			shaderFlags &= VERTEX_FLAG;			

		}
		if(parShader.FTessControl!=BASIC_SHADER)
		{
			std::string tcsFile;
			tessControlShader = glCreateShader(GL_TESS_CONTROL_SHADER);
			ReadFile(parShader.FTessControl.c_str(), tcsFile);
			const char * tcsFile_ptr = tcsFile.c_str();
			glShaderSource(tessControlShader, 1, (const char **)&tcsFile_ptr, NULL);
			glCompileShader(tessControlShader);
			CheckShader(tessControlShader, parShader.FTessControl);
			glAttachShader(programID, tessControlShader);
			shaderFlags &= TESS_CONTROL_FLAG;
			parShader.FIsTesselated =true;	
		}

		if(parShader.FTessEval!=BASIC_SHADER)
		{
			std::string tesFile;
			tessEvalShader = glCreateShader(GL_TESS_EVALUATION_SHADER);
			ReadFile(parShader.FTessEval.c_str(), tesFile);
			const char * tesFile_ptr = tesFile.c_str();
			glShaderSource(tessEvalShader, 1, (const char **)&tesFile_ptr, NULL);
			glCompileShader(tessEvalShader);
			CheckShader(tessEvalShader, parShader.FTessEval);
			glAttachShader(programID, tessEvalShader);
			shaderFlags &= TESS_EVAL_FLAG;	
			parShader.FIsTesselated =true;	
		}

		if(parShader.FGeometryShader!=BASIC_SHADER)
		{
			std::string gsFile;
			geometryShader = glCreateShader(GL_GEOMETRY_SHADER);
			ReadFile(parShader.FGeometryShader.c_str(), gsFile);
			const char * gsFile_ptr = gsFile.c_str();
			glShaderSource(geometryShader, 1, (const char **)&gsFile_ptr, NULL);
			glCompileShader(geometryShader);
			CheckShader(geometryShader, parShader.FGeometryShader);
			glAttachShader(programID, geometryShader);
			shaderFlags &= GEOMETRY_FLAG;			
		}
		if(parShader.FFragmentShader!=BASIC_SHADER)
		{
			std::string fsFile;
			fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
			ReadFile(parShader.FFragmentShader.c_str(), fsFile);
			const char * fsFile_ptr = fsFile.c_str();
			glShaderSource(fragmentShader, 1, (const char **)&fsFile_ptr, NULL);
			glCompileShader(fragmentShader);
			CheckShader(fragmentShader, parShader.FFragmentShader);
			glAttachShader(programID, fragmentShader);
			shaderFlags &= FRAGMENT_FLAG;			
		}

		glLinkProgram(programID);
		if(CheckProgram(programID))
		{
			parShader.FProgramID = programID;
			parShader.FActive = true;
			FPrograms.push_back(parShader);
			GRAPHICS_DEBUG("Shader created");
			// Cleaning up the memory required for compilation
			if(shaderFlags & VERTEX_FLAG)
			{
				glDetachShader(programID, vertexShader);
				glDeleteShader(vertexShader);
			}
			if(shaderFlags & TESS_CONTROL_FLAG)
			{
				glDetachShader(programID, tessControlShader);
				glDeleteShader(tessControlShader);
			}
			if(shaderFlags & TESS_EVAL_FLAG)
			{
				glDetachShader(programID, tessEvalShader);
				glDeleteShader(tessEvalShader);
			}
			if(shaderFlags & GEOMETRY_FLAG)
			{
				glDetachShader(programID, geometryShader);
				glDeleteShader(geometryShader);
			}
			if(shaderFlags & FRAGMENT_FLAG)
			{
				glDetachShader(programID, fragmentShader);
				glDeleteShader(fragmentShader);
			}
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

	void ShaderManager::BindTex(GLuint parIndexTex, GLuint _spot)
	{
   		glActiveTexture(GL_TEXTURE0+_spot);
	    glBindTexture(GL_TEXTURE_2D, parIndexTex);	
	}

	void ShaderManager::BindCubeMap(GLuint parIndexTex, GLuint _spot)
	{
   		glActiveTexture(GL_TEXTURE0+_spot);
	    glBindTexture(GL_TEXTURE_CUBE_MAP, parIndexTex);		
	}

	void ShaderManager::UnbindTex(GLuint _spot)
	{
   		glActiveTexture(GL_TEXTURE0+_spot);
	    glBindTexture(GL_TEXTURE_2D, 0);	
	}

	void ShaderManager::UnbindCubeMap(GLuint _spot)
	{
   		glActiveTexture(GL_TEXTURE0 + _spot);
	    glBindTexture(GL_TEXTURE_CUBE_MAP, 0);		
	}

	// Injections
	void ShaderManager::InjectVec3(const TShader& parProgram, const Vector3& parValue, const std::string& parName)
	{
	    glUniform3f(glGetUniformLocation(parProgram.FProgramID, parName.c_str()), (GLfloat)parValue.x, (GLfloat)parValue.y, (GLfloat)parValue.z);
	}
	void ShaderManager::InjectVec4(const TShader& parProgram, const Vector4& parValue, const std::string& parName)
	{
	    glUniform4f(glGetUniformLocation(parProgram.FProgramID, parName.c_str()), (GLfloat)parValue.x, (GLfloat)parValue.y, (GLfloat)parValue.z, (GLfloat)parValue.w);
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
	void ShaderManager::InjectTex(const TShader& parProgram, GLuint _textureID, const std::string& parName, GLuint _spot)
	{
	    BindTex(_textureID, _spot);
	    GLint texRef = glGetUniformLocation(parProgram.FProgramID, parName.c_str());
	    glUniform1i(texRef, 0 + _spot);
	    //UnbindTex(_spot);
	}

	void ShaderManager::InjectCubeMap(const TShader& parProgram, GLuint _textureID, const std::string& parName, GLuint _spot)
	{
	    BindCubeMap(_textureID, _spot);
	    GLint texRef = glGetUniformLocation(parProgram.FProgramID, parName.c_str());
	    glUniform1i(texRef, 0+_spot);
	    //UnbindCubeMap(_spot);
	}
}
