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


 #include "CubeR.h"
 #include "Render/Defines.h"
 #include "Render/Const.h"
 #include "Base/Common.h"
 #include "MultiThread/Defines.h"
 #include <string.h>


namespace Donut
{

GLfloat cubeVertexL[216] = { 

	// 0 1 2 / 1 2 3
	1.0f, -1.0f, -1.0f, // 0
	-1.0f, -1.0f, -1.0f,// 3
	1.0f, -1.0f, 1.0f,  // 1
	-1.0f, -1.0f, 1.0f, // 2

	// 4 5 6 // 4 6 7 
	1.0f, -1.0f, -1.0f, 
	1.0f, -1.0f, 1.0f,  // 1
  	1.0f, 1.0f, -1.0f,   // 4
	1.0f, 1.0f, 1.0f,    // 5


	1.0f, -1.0f, -1.0f,  // 0
	-1.0f, -1.0f, -1.0f, // 3
  	1.0f, 1.0f, -1.0f,   // 4
	-1.0f, 1.0f, -1.0f,   // 7

	-1.0f, 1.0f, -1.0f,
	-1.0f, 1.0f, 1.0f,
  	1.0f, 1.0f, -1.0f,   // 4
	1.0f, 1.0f, 1.0f,

	1.0f, 1.0f, 1.0f,
	1.0f, -1.0f, 1.0f,
	-1.0f, 1.0f, 1.0f,
	-1.0f, -1.0f, 1.0f,

	-1.0f, 1.0f, 1.0f,
	-1.0f, -1.0f, 1.0f,
	-1.0f, 1.0f, -1.0f,
	-1.0f, -1.0f, -1.0f,

	0.0,-1.0,0.0,
	0.0,-1.0,0.0,
	0.0,-1.0,0.0,
	0.0,-1.0,0.0,
	
	1.0,0.0,0.0,
	1.0,0.0,0.0,
	1.0,0.0,0.0,
	1.0,0.0,0.0,

	0.0,0.0,-1.0,
	0.0,0.0,-1.0,
	0.0,0.0,-1.0,
	0.0,0.0,-1.0,

	0.0,1.0,0.0,
	0.0,1.0,0.0,
	0.0,1.0,0.0,
	0.0,1.0,0.0,

	0.0,0.0,1.0,
	0.0,0.0,1.0,
	0.0,0.0,1.0,
	0.0,0.0,1.0,

	-1.0,0.0,0.0,
	-1.0,0.0,0.0,
	-1.0,0.0,0.0,
	-1.0,0.0,0.0,

	0.0,0.0,
	0.0,1.0,
	1.0,0.0,
	1.0,1.0,

	0.0,0.0,
	0.0,1.0,
	1.0,0.0,
	1.0,1.0,

	0.0,0.0,
	0.0,1.0,
	1.0,0.0,
	1.0,1.0,	

	0.0,0.0,
	0.0,1.0,
	1.0,0.0,
	1.0,1.0,

	0.0,0.0,
	0.0,1.0,
	1.0,0.0,
	1.0,1.0,

	0.0,0.0,
	0.0,1.0,
	1.0,0.0,
	1.0,1.0,	


};

unsigned int cubeFacesL[36] = 
{ 
	0, 1, 2,
	1, 2, 3,

	4, 5, 6,
	5, 6, 7,

	8, 9, 10,
	9, 10, 11,

	12, 13, 14,
	13, 14, 15,

	16, 17, 18,
	17, 18, 19,

	20, 21, 22,
	21, 22, 23
};

 	TCubeR::TCubeR(TVec3 parPosition, float parDimension)
 	: TDrawableObject()
 	, FPosition(parPosition)
 	, FDimension(parDimension)
 	{
 		FModelMatrix = FModelMatrix*Matrix4::translate(parPosition);
 	}

 	TCubeR::~TCubeR()
 	{

 	}

 	void TCubeR::Init()
 	{
 		GLfloat data[216];
 		memcpy(&data ,&cubeVertexL,sizeof(cubeVertexL));

 		for(int i = 0; i<72; ++i)
 		{
 			data[i]*=FDimension;
 		}
		glGenVertexArrays (1, &FVertexArrayID);
		glBindVertexArray (FVertexArrayID);
		
		glGenBuffers(1, &FVBO);
		glBindBuffer(GL_ARRAY_BUFFER, FVBO);

		glBufferData(GL_ARRAY_BUFFER, sizeof(data), data, GL_STATIC_DRAW);

		glGenBuffers(1, &FIBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, FIBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(cubeFacesL), cubeFacesL, GL_STATIC_DRAW);
		GLuint posAtt = glGetAttribLocation(FShader.FProgramID, "position");
		GLuint normalAtt = glGetAttribLocation(FShader.FProgramID, "normal");
		GLuint texCoordAtt = glGetAttribLocation(FShader.FProgramID, "tex_coord");
		glEnableVertexAttribArray (posAtt);
		glEnableVertexAttribArray (normalAtt);
		glEnableVertexAttribArray (texCoordAtt);
		glVertexAttribPointer (posAtt, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glVertexAttribPointer (normalAtt, 3, GL_FLOAT, GL_FALSE, 0, (void*)(sizeof (GLfloat)*72));
		glVertexAttribPointer (texCoordAtt, 2, GL_FLOAT, GL_FALSE, 0, (void*)(sizeof (GLfloat)*144));
		
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray (0);
 	}
 	void TCubeR::SetPosition(const TVec3& parPos)
 	{
 		CRITICAL_SECTION_BEGIN();
 		FPosition = parPos;
 		CRITICAL_SECTION_END();	
 	}
 	
 	void TCubeR::UpdateInfoShader()
 	{
		ShaderManager::Instance().InjectMat4(FShader,FModelMatrix,"model");
 	}

 	void TCubeR::Draw()
 	{	
    	//Clear information from last draw
    	// std::cout<<FVertexArrayID<<" "<<36<<std::endl;

	  	glBindVertexArray (FVertexArrayID);
	  	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	  	glBindVertexArray (0);
 	}
 }