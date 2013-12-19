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
	void CheckShader(GLuint parShaderID)
	{
	    GLint Result = GL_FALSE;
	    int InfoLogLength;
	    
	    glGetShaderiv(parShaderID, GL_COMPILE_STATUS, &Result);
	    glGetShaderiv(parShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);

	    if(InfoLogLength>1)
	    {
	        char errorMessage[InfoLogLength];
	        glGetShaderInfoLog(parShaderID, InfoLogLength, NULL, errorMessage);
	        RENDER_DEBUG( "Shader error:"<< parShaderID);
	        RENDER_ERR( errorMessage );
	    }
	}


	void CheckProgram(GLuint parProgramID)
	{
	    GLint Result = GL_FALSE;
	    int InfoLogLength;
	    
	    glGetProgramiv(parProgramID, GL_LINK_STATUS, &Result);
	    glGetProgramiv(parProgramID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	    if(InfoLogLength>1)
	    {   
	        char errorMessage[InfoLogLength];
	        glGetProgramInfoLog(parProgramID, InfoLogLength, NULL, errorMessage);
	        RENDER_ERR("Program linking error: "<<std::endl<<errorMessage );
	    }
	}

	ShaderManager::ShaderManager()
	: FBasicPipeline (0, " "," ")
	{
	}

	ShaderManager::~ShaderManager()
	{
		
	}

	TShader ShaderManager::CreateShader(const std::string& parVertexShader, const std::string& parFragmentShader)
	{
		GLuint programID;
		GLuint vertexShader;
		GLuint fragmentShader;

		char * vsFile = NULL;
		char * fsFile = NULL;

		vertexShader = glCreateShader(GL_VERTEX_SHADER);
		fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

		vsFile = LoadFile(parVertexShader.c_str());
		fsFile = LoadFile(parFragmentShader.c_str());

		const char * vsFile_ptr = vsFile;
		const char * fsFile_ptr = fsFile;

		glShaderSource(vertexShader, 1, (const char **)&vsFile, NULL);
		glShaderSource(fragmentShader, 1, (const char **)&fsFile, NULL);

		free(vsFile);
		free(fsFile);

		glCompileShader(vertexShader);
		glCompileShader(fragmentShader);
		CheckShader(vertexShader);
		CheckShader(fragmentShader);
		programID = glCreateProgram();
		glAttachShader(programID,vertexShader);
		glAttachShader(programID,fragmentShader);
		glLinkProgram(programID);
		CheckProgram(programID);

		TShader createdProgram(programID,parVertexShader, parFragmentShader);
		createdProgram.FActive = true;
		FPrograms.push_back(createdProgram);

		
		return createdProgram;
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


	void ShaderManager::InjectInt(const TShader& parProgram, int parValue, const std::string& parName)
	{
	    glUniform1i(glGetUniformLocation(parProgram.FProgramID, parName.c_str()), parValue);
	}

	void ShaderManager::InjectMat4(const TShader& parProgram, const Matrix4& parValue, const std::string& parName)
	{
		float mat[16];
		parValue.toTable(&mat[0]);
 		//RENDER_DEBUG(parName<<" "<<mat[0]<<" "<<mat[1]<<" "<<mat[2]<<" "<<mat[3]<<" "<<mat[4]<<" "<<mat[5]<<" "<<mat[6]<<" "<<mat[7]<<" "<<mat[8]<<" "<<mat[9]<<" "<<mat[10]<<" "<<mat[11]<<" "<<mat[12]<<" "<<mat[13]<<" "<<mat[14]<<" "<<mat[15]);
	    glUniformMatrix4fv(glGetUniformLocation(parProgram.FProgramID, parName.c_str()),1,true, mat);
	}
	void ShaderManager::InjectTex(const TShader& parProgram, size_t parIndexTex, const std::string& parName, GLuint parOffset)
	{
	   	glActiveTexture(GL_TEXTURE0+parOffset);
	    glBindTexture(GL_TEXTURE_2D, parIndexTex);
	    GLint texRef = glGetUniformLocation(parProgram.FProgramID, parName.c_str());
	    glUniform1i(texRef, 0+parOffset);
	}
}