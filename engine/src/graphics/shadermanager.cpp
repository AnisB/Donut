// Bento includes
#include <bento_base/security.h>

// Library includes
#include "graphics/shadermanager.h"
#include "graphics/material.h"
#include "resource/resourcemanager.h"
#include "gpu_backend/gl_factory.h"

#include "tools/fileloader.h"

// Bento includes
#include <bento_math/matrix3.h>

// STL includes
#include <stdlib.h>

// External includes
#include <GL/glew.h>
#ifndef GLFW_INCLUDE_GL3
#define GLFW_INCLUDE_GL3
#endif
#include <GLFW/glfw3.h>

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
		GL_API_CHECK();
		// Here we should delete all the shaders that where created
		for(auto& shader : FPrograms)
		{
			glDeleteProgram(shader.FProgramID);
		}

 		GL_API_CHECK();
	}

	bool ShaderManager::CreateShader(TShader& _shader)
	{
		GL_API_CHECK();

		// We make shure the shader was not created before
		auto& result = FPrograms.find(_shader);
		if(result != FPrograms.end())
		{
			_shader.FProgramID = result->FProgramID;
			_shader.FActive = result->FActive;
			_shader.FIsTesselated = result->FIsTesselated;
			return true;
		}

		// If it is not, we create it
		TShaderFileHandler& shaderFileHandler = TShaderFileHandler::Instance();
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
			GL_API_CHECK();
			return true;
		}
		else
		{
			assert_fail_msg("Shader creation failed.");
			GL_API_CHECK();
			return false;
		}
	}

	void ShaderManager::EnableShader(const TShader& _program)
	{
		GL_API_CHECK();
		assert(_program.FActive);
		glUseProgram(_program.FProgramID);
		GL_API_CHECK();
	}

	void ShaderManager::DisableShader()
	{
		GL_API_CHECK();
		glUseProgram(0);
		GL_API_CHECK();
	}

	void ShaderManager::BindTex(GLuint parIndexTex, GLuint _spot)
	{
		GL_API_CHECK();
		glActiveTexture(GL_TEXTURE0+_spot);
	    glBindTexture(GL_TEXTURE_2D, parIndexTex);	
		GL_API_CHECK();
	}

	void ShaderManager::BindCubeMap(GLuint parIndexTex, GLuint _spot)
	{
		GL_API_CHECK();
   		glActiveTexture(GL_TEXTURE0+_spot);
	    glBindTexture(GL_TEXTURE_CUBE_MAP, parIndexTex);		
		GL_API_CHECK();
	}

	void ShaderManager::UnbindTex(GLuint _spot)
	{
		GL_API_CHECK();
		glActiveTexture(GL_TEXTURE0+_spot);
	    glBindTexture(GL_TEXTURE_2D, 0);
		GL_API_CHECK();
	}

	void ShaderManager::UnbindCubeMap(GLuint _spot)
	{
		GL_API_CHECK();
		glActiveTexture(GL_TEXTURE0 + _spot);
	    glBindTexture(GL_TEXTURE_CUBE_MAP, 0);		
		GL_API_CHECK();
	}

	// Injections
	template <>
	void ShaderManager::Inject(const TShader& parProgram, const bento::Vector3& parValue, const STRING_TYPE& parName)
	{
		GL_API_CHECK();
		glUniform3f(glGetUniformLocation(parProgram.FProgramID, parName.c_str()), (GLfloat)parValue.x, (GLfloat)parValue.y, (GLfloat)parValue.z);
		GL_API_CHECK();
	}
	template <>
	void ShaderManager::Inject(const TShader& parProgram, const bento::Vector4& _value, const STRING_TYPE& parName)
	{
		GL_API_CHECK();
		glUniform4f(glGetUniformLocation(parProgram.FProgramID, parName.c_str()), (GLfloat)_value.x, (GLfloat)_value.y, (GLfloat)_value.z, (GLfloat)_value.w);
		GL_API_CHECK();
	}
	
 	template <>
	void ShaderManager::Inject(const TShader& parProgram, const int& _value, const STRING_TYPE& parName)
	{
		GL_API_CHECK();
		GLuint location = glGetUniformLocation(parProgram.FProgramID, parName.c_str());
	    glUniform1i(location, _value);
		GL_API_CHECK();
	}

 	template <>
	void ShaderManager::Inject(const TShader& parProgram, const float& _value, const STRING_TYPE& parName)
	{
		GL_API_CHECK();
	    glUniform1f( glGetUniformLocation(parProgram.FProgramID, parName.c_str()), _value);
		GL_API_CHECK();
	}

	template <>
	void ShaderManager::InjectV(const TShader& parProgram, const float* _values, int _nbValues, const STRING_TYPE& parName)
	{
		GL_API_CHECK();
	    glUniform1fv( glGetUniformLocation(parProgram.FProgramID, parName.c_str()),_nbValues, _values);
		GL_API_CHECK();
	}

 	template <>
	void ShaderManager::Inject(const TShader& parProgram, const bento::Matrix4& parValue, const STRING_TYPE& parName)
	{
		GL_API_CHECK();
		float mat[16];
		ToTable(parValue, &mat[0]);
	    glUniformMatrix4fv(glGetUniformLocation(parProgram.FProgramID, parName.c_str()),1,true, mat);
		GL_API_CHECK();
	}

 	template <>
	void ShaderManager::Inject(const TShader& parProgram, const bento::Matrix3& parValue, const STRING_TYPE& parName)
	{
		GL_API_CHECK();
		glUniformMatrix3fv(glGetUniformLocation(parProgram.FProgramID, parName.c_str()),1,true, parValue.m);
		GL_API_CHECK();
	}

	void ShaderManager::InjectTex(const TShader& parProgram, GLuint _textureID, const STRING_TYPE& parName, GLuint _spot)
	{
		GL_API_CHECK();
		BindTex(_textureID, _spot);
	    GLint texRef = glGetUniformLocation(parProgram.FProgramID, parName.c_str());
	    glUniform1i(texRef, 0 + _spot);
	    //UnbindTex(_spot);
		GL_API_CHECK();
	}

	void ShaderManager::InjectCubeMap(const TShader& parProgram, GLuint _textureID, const STRING_TYPE& parName, GLuint _spot)
	{
		GL_API_CHECK();
		BindCubeMap(_textureID, _spot);
	    GLint texRef = glGetUniformLocation(parProgram.FProgramID, parName.c_str());
	    glUniform1i(texRef, 0+_spot);
	    //UnbindCubeMap(_spot);
		GL_API_CHECK();
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
