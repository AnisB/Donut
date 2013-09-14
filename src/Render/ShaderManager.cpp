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
 #include "Tools/FileLoader.h"

namespace Donut 
{
	ShaderManager::ShaderManager()
	: FBasicPipeline (0)
	{
	}

	ShaderManager::~ShaderManager()
	{
		
	}

	TProgram ShaderManager::CreateShader(char* parVertexShader, char* parFragmentShader)
	{
		GLuint programID;
		GLuint vertexShader;
		GLuint fragmentShader;

		char * vsFile = NULL;
		char * fsFile = NULL;

		vertexShader = glCreateShader(GL_VERTEX_SHADER);
		fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

		vsFile = LoadFile(parVertexShader);
		fsFile = LoadFile(parFragmentShader);

		const char * vsFile_ptr = vsFile;
		const char * fsFile_ptr = fsFile;

		glShaderSource(vertexShader, 1, (const char **)&vsFile, NULL);
		glShaderSource(fragmentShader, 1, (const char **)&fsFile, NULL);

		free(vsFile);
		free(fsFile);

		glCompileShader(vertexShader);
		glCompileShader(fragmentShader);

		programID = glCreateProgram();
		glAttachShader(programID,vertexShader);
		glAttachShader(programID,fragmentShader);
		glLinkProgram(programID);

		TProgram createdProgram(programID);
		FPrograms.push_back(createdProgram);
		return createdProgram;
	}

	void ShaderManager::EnableShader(const TProgram& parProgram)
	{
		glUseProgram(parProgram.FProgramID);
	}

	void ShaderManager::DisableShader()
	{
		glUseProgram(FBasicPipeline.FProgramID);
	}
}