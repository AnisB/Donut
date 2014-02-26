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
 #include <Base/DebugPrinters.h>

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
	        char errorMessage[InfoLogLength];
	        glGetShaderInfoLog(parShaderID, InfoLogLength, NULL, errorMessage);
	        RENDER_DEBUG( "Shader error:"<<parShadePath<<" "<<parShaderID);
	        RENDER_ERR( errorMessage );
	    }
	}


	bool CheckProgram(GLuint parProgramID,const std::string& parVShadePath, const std::string& parGShadePath,  const std::string& parFShadePath)
	{
	    GLint Result = GL_FALSE;
	    int InfoLogLength;
	    
	    glGetProgramiv(parProgramID, GL_LINK_STATUS, &Result);
	    glGetProgramiv(parProgramID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	    if(InfoLogLength>1)
	    {   
	        char errorMessage[InfoLogLength];
	        glGetProgramInfoLog(parProgramID, InfoLogLength, NULL, errorMessage);
	        RENDER_ERR("Program linking error: "<<parVShadePath<<" "<<parGShadePath<<" "<<parFShadePath<<std::endl<<errorMessage );
	        return false;
	    }
	    return true;
	}

	ShaderManager::ShaderManager()
	: FBasicPipeline (0, " "," ", " ")
	{
	}

	ShaderManager::~ShaderManager()
	{
		
	}

	bool ShaderManager::CreateShader(TShader& parShader)
	{
		GLuint programID;
		GLuint vertexShader;
		GLuint geometryShader;
		GLuint fragmentShader;

		programID = glCreateProgram();

		if(parShader.FVertexShader != BASIC_VERTEX_SHADER)
		{
			char * vsFile = NULL;
			vertexShader = glCreateShader(GL_VERTEX_SHADER);
			vsFile = LoadFile(parShader.FVertexShader.c_str());
			const char * vsFile_ptr = vsFile;
			glShaderSource(vertexShader, 1, (const char **)&vsFile, NULL);
			free(vsFile);
			glCompileShader(vertexShader);
			CheckShader(vertexShader, parShader.FVertexShader);
			glAttachShader(programID,vertexShader);			
		}

		if(parShader.FFragmentShader != BASIC_FRAGMENT_SHADER)
		{
			char * fsFile = NULL;
			fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
			fsFile = LoadFile(parShader.FFragmentShader.c_str());
			const char * fsFile_ptr = fsFile;
			glShaderSource(fragmentShader, 1, (const char **)&fsFile, NULL);
			free(fsFile);
			glCompileShader(fragmentShader);
			CheckShader(fragmentShader, parShader.FFragmentShader);
			glAttachShader(programID,fragmentShader);
		
		}
		if(parShader.FGeometryShader != BASIC_GEOMETRY_SHADER)
		{
			char * gsFile = NULL;
			geometryShader = glCreateShader(GL_GEOMETRY_SHADER);
			gsFile = LoadFile(parShader.FGeometryShader.c_str());
			const char * gsFile_ptr = gsFile;
			glShaderSource(geometryShader, 1, (const char **)&gsFile, NULL);
			free(gsFile);
			glCompileShader(geometryShader);
			CheckShader(geometryShader, parShader.FGeometryShader);
			glAttachShader(programID,geometryShader);
		}

		glLinkProgram(programID);
		if(CheckProgram(programID,parShader.FVertexShader, parShader.FGeometryShader, parShader.FFragmentShader))
		{
			parShader.FProgramID = programID;
			parShader.FActive = true;
			FPrograms.push_back(parShader);
			return true;
		}
		else
		{
			return false;
		}


	}

	void ShaderManager::EnableShader(const TShader& parProgram)
	{
		AssertNoRelease(parProgram.FActive);
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
	void ShaderManager::InjectVec3(const TShader& parProgram, const TVec3& parValue, const std::string& parName)
	{
	    glUniform3f(glGetUniformLocation(parProgram.FProgramID, parName.c_str()), parValue.val[0], parValue.val[1], parValue.val[2]);
	}
	void ShaderManager::InjectVec4(const TShader& parProgram, const TVec4& parValue, const std::string& parName)
	{
	    glUniform4f(glGetUniformLocation(parProgram.FProgramID, parName.c_str()), parValue.val[0], parValue.val[1], parValue.val[2],parValue.val[3]);

	}

	void ShaderManager::InjectInt(const TShader& parProgram, int parValue, const std::string& parName)
	{
	    glUniform1i(glGetUniformLocation(parProgram.FProgramID, parName.c_str()), parValue);
	}
	void ShaderManager::InjectFloat(const TShader& parProgram, float parValue, const std::string& parName)
	{
	    glUniform1f(glGetUniformLocation(parProgram.FProgramID, parName.c_str()), parValue);
	}
	void ShaderManager::InjectMat4(const TShader& parProgram, const Matrix4& parValue, const std::string& parName)
	{
		float mat[16];
		parValue.toTable(&mat[0]);
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
		foreach(tex,parSugar.textures)
		{
			ShaderManager::Instance().BindTex(tex->texID, tex->index);
		}
	}

}