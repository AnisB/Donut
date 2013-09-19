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
	: FBasicPipeline (0, " "," ")
	{
	}

	ShaderManager::~ShaderManager()
	{
		
	}

	TShader ShaderManager::CreateShader(std::string parVertexShader, std::string parFragmentShader)
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
		PrintLog(vertexShader);
		PrintLog(fragmentShader);
		programID = glCreateProgram();
		glAttachShader(programID,vertexShader);
		glAttachShader(programID,fragmentShader);
		glLinkProgram(programID);
		PrintLog(programID);

		TShader createdProgram(programID,parVertexShader, parFragmentShader);
		createdProgram.FActive = true;
		FPrograms.push_back(createdProgram);

		
		return createdProgram;
	}

	void ShaderManager::PrintLog(GLuint parProg)
	{
		int infologLength = 0;
		int charsWritten  = 0;
		char *infoLog;

	   // afficher le message d'erreur, le cas échéant
		glGetShaderiv(parProg, GL_INFO_LOG_LENGTH,&infologLength);

		if (infologLength > 1)
		{
			infoLog = (char *)malloc(infologLength);
			glGetShaderInfoLog(parProg, infologLength, &charsWritten, infoLog);
			printf("%s\n",infoLog);
			free(infoLog);
		} 
	}


	void ShaderManager::EnableShader(const TShader& parProgram)
	{
		if(parProgram.FActive)
		{
			glUseProgram(parProgram.FProgramID);
		}
	}

	void ShaderManager::DisableShader()
	{
		glUseProgram(FBasicPipeline.FProgramID);
	}
}