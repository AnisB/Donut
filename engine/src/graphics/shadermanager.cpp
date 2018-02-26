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
#include "graphics/shadermanager.h"
#include "graphics/common.h"
#include "graphics/material.h"
#include "resource/resourcemanager.h"
#include "graphics/glfactory.h"
#include "butter/stream.h"
#include "butter/matrix3.h"

#include "tools/fileloader.h"

// STL includes
#include <stdlib.h>

namespace donut 
{
	void CheckShader(GLuint _shaderID, const STRING_TYPE& _shaderFileName)
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
 		GL_API_CHECK_START();

		// Here we should delete all the shaders that where created
		for(auto& shader : FPrograms)
		{
			glDeleteProgram(shader.FProgramID);
		}

 		GL_API_CHECK_END();
	}

	bool ShaderManager::CreateShader(TShader& _shader)
	{
 		GL_API_CHECK_START();

		// We make shure the shader was not created before
		GRAPHICS_DEBUG("Fetching shader kernel");
		auto& result = FPrograms.find(_shader);
		if(result != FPrograms.end())
		{
			GRAPHICS_DEBUG("Already created shader kernel");
			_shader.FProgramID = result->FProgramID;
			_shader.FActive = result->FActive;
			_shader.FIsTesselated = result->FIsTesselated;
 			GL_API_CHECK_END();
			return true;
		}

		// If it is not, we create it
		TShaderFileHandler& shaderFileHandler = TShaderFileHandler::Instance();
		GRAPHICS_DEBUG("Creating shader kernel");
		GLuint programID = 0;
		GLuint vertexShader = 0;
		GLuint tessControlShader = 0;
		GLuint tessEvalShader = 0;
		GLuint geometryShader = 0;
		GLuint fragmentShader = 0;

		programID = glCreateProgram();
		char shaderFlags = 0;
		if(_shader.FVertexShader!=BASIC_SHADER)
		{
			STRING_TYPE vsFile;
			vertexShader = glCreateShader(GL_VERTEX_SHADER);
			const STRING_TYPE& vertexShaderFileName = shaderFileHandler.GetShaderFile(_shader.FVertexShader);
			GRAPHICS_DEBUG(vertexShaderFileName);
            ReadFile(ResourceManager::Instance().RelativePath(vertexShaderFileName).c_str(),vsFile);
			const char * vsFile_ptr = vsFile.c_str();
			glShaderSource(vertexShader, 1, (const char **)&vsFile_ptr, NULL);
			glCompileShader(vertexShader);
			CheckShader(vertexShader, vertexShaderFileName);
			glAttachShader(programID, vertexShader);
			shaderFlags &= VERTEX_FLAG;			

		}
		if(_shader.FTessControl!=BASIC_SHADER)
		{
			STRING_TYPE tcsFile;
			const STRING_TYPE& tessControlShaderFileName = shaderFileHandler.GetShaderFile(_shader.FTessControl);
			tessControlShader = glCreateShader(GL_TESS_CONTROL_SHADER);
            ReadFile(ResourceManager::Instance().RelativePath(tessControlShaderFileName).c_str(),tcsFile);
			const char * tcsFile_ptr = tcsFile.c_str();
			glShaderSource(tessControlShader, 1, (const char **)&tcsFile_ptr, NULL);
			glCompileShader(tessControlShader);
			CheckShader(tessControlShader, tessControlShaderFileName);
			glAttachShader(programID, tessControlShader);
			shaderFlags &= TESS_CONTROL_FLAG;
			_shader.FIsTesselated =true;	
		}

		if(_shader.FTessEval!=BASIC_SHADER)
		{
			STRING_TYPE tesFile;
			const STRING_TYPE& tessEvalShaderFileName = shaderFileHandler.GetShaderFile(_shader.FTessEval);
			tessEvalShader = glCreateShader(GL_TESS_EVALUATION_SHADER);
            ReadFile(ResourceManager::Instance().RelativePath(tessEvalShaderFileName).c_str(),tesFile);
			const char * tesFile_ptr = tesFile.c_str();
			glShaderSource(tessEvalShader, 1, (const char **)&tesFile_ptr, NULL);
			glCompileShader(tessEvalShader);
			CheckShader(tessEvalShader, tessEvalShaderFileName);
			glAttachShader(programID, tessEvalShader);
			shaderFlags &= TESS_EVAL_FLAG;	
			_shader.FIsTesselated =true;	
		}

		if(_shader.FGeometryShader!=BASIC_SHADER)
		{
			STRING_TYPE gsFile;
			const STRING_TYPE& geometryShaderFileName = shaderFileHandler.GetShaderFile(_shader.FGeometryShader);
			geometryShader = glCreateShader(GL_GEOMETRY_SHADER);
            ReadFile(ResourceManager::Instance().RelativePath(geometryShaderFileName).c_str(),gsFile);
			const char * gsFile_ptr = gsFile.c_str();
			glShaderSource(geometryShader, 1, (const char **)&gsFile_ptr, NULL);
			glCompileShader(geometryShader);
			CheckShader(geometryShader, geometryShaderFileName);
			glAttachShader(programID, geometryShader);
			shaderFlags &= GEOMETRY_FLAG;			
		}
		if(_shader.FFragmentShader!=BASIC_SHADER)
		{
			STRING_TYPE fsFile;
			const STRING_TYPE& fragmentShaderFileName = shaderFileHandler.GetShaderFile(_shader.FFragmentShader);
			fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
            ReadFile(ResourceManager::Instance().RelativePath(fragmentShaderFileName).c_str(), fsFile);
			const char * fsFile_ptr = fsFile.c_str();
			glShaderSource(fragmentShader, 1, (const char **)&fsFile_ptr, NULL);
			glCompileShader(fragmentShader);
			CheckShader(fragmentShader, fragmentShaderFileName);
			glAttachShader(programID, fragmentShader);
			shaderFlags &= FRAGMENT_FLAG;			
		}

		glLinkProgram(programID);
		if(CheckProgram(programID))
		{
			_shader.FProgramID = programID;
			_shader.FActive = true;
			FPrograms.insert(_shader);
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
 			GL_API_CHECK_END();
			return true;
		}
		else
		{
			ASSERT_FAIL_MSG_NO_RELEASE("Shader creation failed.");
 			GL_API_CHECK_END();
			return false;
		}
	}

	void ShaderManager::EnableShader(const TShader& _program)
	{
		GL_API_CHECK_START();
		ASSERT_NO_RELEASE(_program.FActive);
		glUseProgram(_program.FProgramID);
		GL_API_CHECK_END();
	}

	void ShaderManager::DisableShader()
	{
		GL_API_CHECK_START();
		glUseProgram(0);
		GL_API_CHECK_END();
	}

	void ShaderManager::BindTex(GLuint parIndexTex, GLuint _spot)
	{
		GL_API_CHECK_START();
   		glActiveTexture(GL_TEXTURE0+_spot);
	    glBindTexture(GL_TEXTURE_2D, parIndexTex);	
		GL_API_CHECK_END();
	}

	void ShaderManager::BindCubeMap(GLuint parIndexTex, GLuint _spot)
	{
		GL_API_CHECK_START();
   		glActiveTexture(GL_TEXTURE0+_spot);
	    glBindTexture(GL_TEXTURE_CUBE_MAP, parIndexTex);		
		GL_API_CHECK_END();
	}

	void ShaderManager::UnbindTex(GLuint _spot)
	{
		GL_API_CHECK_START();
   		glActiveTexture(GL_TEXTURE0+_spot);
	    glBindTexture(GL_TEXTURE_2D, 0);
		GL_API_CHECK_END();
	}

	void ShaderManager::UnbindCubeMap(GLuint _spot)
	{
		GL_API_CHECK_START();
   		glActiveTexture(GL_TEXTURE0 + _spot);
	    glBindTexture(GL_TEXTURE_CUBE_MAP, 0);		
		GL_API_CHECK_END();
	}

	// Injections
	template <>
	void ShaderManager::Inject(const TShader& parProgram, const Vector3& parValue, const STRING_TYPE& parName)
	{
		GL_API_CHECK_START();
	    glUniform3f(glGetUniformLocation(parProgram.FProgramID, parName.c_str()), (GLfloat)parValue.x, (GLfloat)parValue.y, (GLfloat)parValue.z);
		GL_API_CHECK_END();
	}
	template <>
	void ShaderManager::Inject(const TShader& parProgram, const Vector4& _value, const STRING_TYPE& parName)
	{
		GL_API_CHECK_START();
	    glUniform4f(glGetUniformLocation(parProgram.FProgramID, parName.c_str()), (GLfloat)_value.x, (GLfloat)_value.y, (GLfloat)_value.z, (GLfloat)_value.w);
		GL_API_CHECK_END();
	}
	
 	template <>
	void ShaderManager::Inject(const TShader& parProgram, const int& _value, const STRING_TYPE& parName)
	{
		GL_API_CHECK_START();
		GLuint location = glGetUniformLocation(parProgram.FProgramID, parName.c_str());
	    glUniform1i(location, _value);
		GL_API_CHECK_END();
	}

 	template <>
	void ShaderManager::Inject(const TShader& parProgram, const float& _value, const STRING_TYPE& parName)
	{
		GL_API_CHECK_START();
	    glUniform1f( glGetUniformLocation(parProgram.FProgramID, parName.c_str()), _value);
		GL_API_CHECK_END();
	}

	template <>
	void ShaderManager::InjectV(const TShader& parProgram, const float* _values, int _nbValues, const STRING_TYPE& parName)
	{
		GL_API_CHECK_START();
	    glUniform1fv( glGetUniformLocation(parProgram.FProgramID, parName.c_str()),_nbValues, _values);
		GL_API_CHECK_END();
	}

 	template <>
	void ShaderManager::Inject(const TShader& parProgram, const Matrix4& parValue, const STRING_TYPE& parName)
	{
		GL_API_CHECK_START();
		float mat[16];
		ToTable(parValue, &mat[0]);
	    glUniformMatrix4fv(glGetUniformLocation(parProgram.FProgramID, parName.c_str()),1,true, mat);
		GL_API_CHECK_END();
	}

 	template <>
	void ShaderManager::Inject(const TShader& parProgram, const Matrix3& parValue, const STRING_TYPE& parName)
	{
		GL_API_CHECK_START();
		float mat[9];
		ToTable(parValue, &mat[0]);
	    glUniformMatrix3fv(glGetUniformLocation(parProgram.FProgramID, parName.c_str()),1,true, mat);
		GL_API_CHECK_END();
	}

	void ShaderManager::InjectTex(const TShader& parProgram, GLuint _textureID, const STRING_TYPE& parName, GLuint _spot)
	{
		GL_API_CHECK_START();
	    BindTex(_textureID, _spot);
	    GLint texRef = glGetUniformLocation(parProgram.FProgramID, parName.c_str());
	    glUniform1i(texRef, 0 + _spot);
	    //UnbindTex(_spot);
		GL_API_CHECK_END();
	}

	void ShaderManager::InjectCubeMap(const TShader& parProgram, GLuint _textureID, const STRING_TYPE& parName, GLuint _spot)
	{
		GL_API_CHECK_START();
	    BindCubeMap(_textureID, _spot);
	    GLint texRef = glGetUniformLocation(parProgram.FProgramID, parName.c_str());
	    glUniform1i(texRef, 0+_spot);
	    //UnbindCubeMap(_spot);
		GL_API_CHECK_END();
	}

	void ShaderManager::InjectMaterial(const TShader& _shader, const TMaterial& _material)
	{
		for(auto& uni : _material.uniforms)
		{
			uni.Inject(_shader);
		}
		for(auto& tex : _material.textures)
		{
			ShaderManager::Instance().InjectTex(_shader, tex.texID, tex.name, tex.offset);
		}
	}
}
