// Bento includes
#include <bento_base/security.h>
#include <bento_base/log.h>
#include <bento_collection/vector.h>
#include <bento_tools/file_system.h>

// Library includes
#include "graphics/shadermanager.h"
#include "graphics/material.h"
#include "resource/resource_manager.h"
#include "gpu_backend/gl_factory.h"

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
	void CheckShader(GLuint _shaderID)
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
			bento::default_logger()->log(bento::LogLevel::error, "SHADER_COMPILER", errorMessage);
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
			bento::default_logger()->log(bento::LogLevel::error, "SHADER_COMPILER", errorMessage);
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
		for(auto& shader : _programs)
		{
			glDeleteProgram((GLuint)shader);
		}

 		GL_API_CHECK();
	}

	ShaderPipelineObject ShaderManager::create_shader(const char* vertex_shader, const char* tess_control_shader, 
													const char* tess_eval_shader, const char* geometry_shader, 
													const char* fragment_shader)
	{
		GL_API_CHECK();

		uint32_t program_id = 0;

		GLuint vertexShader = 0;
		GLuint tessControlShader = 0;
		GLuint tessEvalShader = 0;
		GLuint geometryShader = 0;
		GLuint fragmentShader = 0;

		program_id = glCreateProgram();

		char shaderFlags = 0;
		if(vertex_shader != nullptr)
		{
			vertexShader = glCreateShader(GL_VERTEX_SHADER);
			const char * vsFile_ptr = vertex_shader;
			glShaderSource(vertexShader, 1, (const char **)&vsFile_ptr, NULL);
			glCompileShader(vertexShader);
			CheckShader(vertexShader);
			glAttachShader(program_id, vertexShader);
			shaderFlags &= VERTEX_FLAG;			

		}
		if (tess_control_shader != nullptr)
		{
			tessControlShader = glCreateShader(GL_TESS_CONTROL_SHADER);
			const char * tcsFile_ptr = tess_control_shader;
			glShaderSource(tessControlShader, 1, (const char **)&tcsFile_ptr, NULL);
			glCompileShader(tessControlShader);
			CheckShader(tessControlShader);
			glAttachShader(program_id, tessControlShader);
			shaderFlags &= TESS_CONTROL_FLAG;
		}

		if (tess_eval_shader != nullptr)
		{
			tessEvalShader = glCreateShader(GL_TESS_EVALUATION_SHADER);
			const char * tesFile_ptr = tess_eval_shader;
			glShaderSource(tessEvalShader, 1, (const char **)&tesFile_ptr, NULL);
			glCompileShader(tessEvalShader);
			CheckShader(tessEvalShader);
			glAttachShader(program_id, tessEvalShader);
			shaderFlags &= TESS_EVAL_FLAG;	
		}

		if (geometry_shader != nullptr)
		{
			geometryShader = glCreateShader(GL_GEOMETRY_SHADER);
			const char * gsFile_ptr = geometry_shader;
			glShaderSource(geometryShader, 1, (const char **)&gsFile_ptr, NULL);
			glCompileShader(geometryShader);
			glAttachShader(program_id, geometryShader);
			shaderFlags &= GEOMETRY_FLAG;			
		}

		if (fragment_shader != nullptr)
		{
			fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
			const char * fsFile_ptr = fragment_shader;
			glShaderSource(fragmentShader, 1, (const char **)&fsFile_ptr, NULL);
			glCompileShader(fragmentShader);
			CheckShader(fragmentShader);
			glAttachShader(program_id, fragmentShader);
			shaderFlags &= FRAGMENT_FLAG;			
		}

		glLinkProgram(program_id);
		if(CheckProgram(program_id))
		{
			_programs.push_back(program_id);
			// Cleaning up the memory required for compilation
			if(shaderFlags & VERTEX_FLAG)
			{
				glDetachShader(program_id, vertexShader);
				glDeleteShader(vertexShader);
			}
			if(shaderFlags & TESS_CONTROL_FLAG)
			{
				glDetachShader(program_id, tessControlShader);
				glDeleteShader(tessControlShader);
			}
			if(shaderFlags & TESS_EVAL_FLAG)
			{
				glDetachShader(program_id, tessEvalShader);
				glDeleteShader(tessEvalShader);
			}
			if(shaderFlags & GEOMETRY_FLAG)
			{
				glDetachShader(program_id, geometryShader);
				glDeleteShader(geometryShader);
			}
			if(shaderFlags & FRAGMENT_FLAG)
			{
				glDetachShader(program_id, fragmentShader);
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

	void ShaderManager::EnableShader(ShaderPipelineObject _program)
	{
		GL_API_CHECK();
		glUseProgram((GLuint)_program);
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
	void ShaderManager::Inject(ShaderPipelineObject parProgram, const bento::Vector3& parValue, const char* parName)
	{
		GL_API_CHECK();
		glUniform3f(glGetUniformLocation((GLuint)parProgram, parName), (GLfloat)parValue.x, (GLfloat)parValue.y, (GLfloat)parValue.z);
		GL_API_CHECK();
	}
	template <>
	void ShaderManager::Inject(ShaderPipelineObject parProgram, const bento::Vector4& _value, const char* parName)
	{
		GL_API_CHECK();
		glUniform4f(glGetUniformLocation((GLuint)parProgram, parName), (GLfloat)_value.x, (GLfloat)_value.y, (GLfloat)_value.z, (GLfloat)_value.w);
		GL_API_CHECK();
	}
	
 	template <>
	void ShaderManager::Inject(ShaderPipelineObject parProgram, const int& _value, const char* parName)
	{
		GL_API_CHECK();
		GLuint location = glGetUniformLocation((GLuint)parProgram, parName);
	    glUniform1i(location, _value);
		GL_API_CHECK();
	}

 	template <>
	void ShaderManager::Inject(ShaderPipelineObject parProgram, const float& _value, const char* parName)
	{
		GL_API_CHECK();
	    glUniform1f( glGetUniformLocation((GLuint)parProgram, parName), _value);
		GL_API_CHECK();
	}

	template <>
	void ShaderManager::InjectV(ShaderPipelineObject parProgram, const float* _values, int _nbValues, const char* parName)
	{
		GL_API_CHECK();
	    glUniform1fv( glGetUniformLocation((GLuint)parProgram, parName),_nbValues, _values);
		GL_API_CHECK();
	}

 	template <>
	void ShaderManager::Inject(ShaderPipelineObject parProgram, const bento::Matrix4& parValue, const char* parName)
	{
		GL_API_CHECK();
		float mat[16];
		ToTable(parValue, &mat[0]);
	    glUniformMatrix4fv(glGetUniformLocation((GLuint)parProgram, parName),1,true, mat);
		GL_API_CHECK();
	}

 	template <>
	void ShaderManager::Inject(ShaderPipelineObject parProgram, const bento::Matrix3& parValue, const char* parName)
	{
		GL_API_CHECK();
		glUniformMatrix3fv(glGetUniformLocation((GLuint)parProgram, parName),1,true, parValue.m);
		GL_API_CHECK();
	}

	void ShaderManager::InjectTex(ShaderPipelineObject parProgram, GLuint _textureID, const char* parName, GLuint _spot)
	{
		GL_API_CHECK();
		BindTex(_textureID, _spot);
	    GLint texRef = glGetUniformLocation((GLuint)parProgram, parName);
	    glUniform1i(texRef, 0 + _spot);
		GL_API_CHECK();
	}

	void ShaderManager::InjectCubeMap(ShaderPipelineObject parProgram, GLuint _textureID, const char* parName, GLuint _spot)
	{
		GL_API_CHECK();
		BindCubeMap(_textureID, _spot);
	    GLint texRef = glGetUniformLocation(parProgram, parName);
	    glUniform1i(texRef, 0+_spot);
		GL_API_CHECK();
	}

	void ShaderManager::InjectMaterial(ShaderPipelineObject _shader, const TMaterial& _material)
	{
		for(auto& uni : _material.uniforms)
		{
			uni.inject(_shader);
		}
		for(auto& tex : _material.textures)
		{
			ShaderManager::Instance().InjectTex(_shader, tex.id, tex.name.c_str(), tex.offset);
		}
		for (auto& tex : _material.cubeMaps)
		{
			ShaderManager::Instance().InjectCubeMap(_shader, tex.id, tex.name.c_str(), tex.offset);
		}
	}
}
