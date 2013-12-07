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


namespace Donut{
 	TCubeR::TCubeR(float3 parPosition, float parDimension)
 	: TDrawableObject()
 	, FPosition(parPosition)
 	, FDimension(parDimension)
 	, FRotationAngles(0,0,0)
 	{
 		FCubeVertex = new float[24];
 		FCubeIndex = new unsigned[24];
 		memcpy(&FCubeVertex ,&cubeVertex,sizeof(float)*24);
 		memcpy(&FCubeIndex ,&cubeFaces,sizeof(unsigned int)*24);
 	}

 	TCubeR::~TCubeR()
 	{

 	}

 	void TCubeR::Init()
 	{
		glGenBuffers(1, &FVBO);
		glBindBuffer(GL_ARRAY_BUFFER, FVBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(FCubeVertex), &(FCubeVertex), GL_DYNAMIC_DRAW);

		glGenBuffers(1, &FIBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, FIBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(FCubeIndex), &FCubeIndex, GL_STATIC_DRAW);
 	}
 	void TCubeR::SetPosition(const float3& parPos)
 	{
 		CRITICAL_SECTION_BEGIN();
 		FPosition = parPos;
 		CRITICAL_SECTION_END();	
 	}

 	void TCubeR::SetRotation(const float3& parAngle)
 	{
 		FRotationAngles = parAngle;
 	}

 	void TCubeR::Draw()
 	{
 		
    //Clear information from last draw

 		CRITICAL_SECTION_BEGIN();
 		glPushMatrix();
 		glTranslatef(FPosition.x, FPosition.y, FPosition.z);
 		glRotatef(FRotationAngles.x,1.0,0.0,0.0);
 		glRotatef(FRotationAngles.y,0.0,1.0,0.0);
 		glRotatef(FRotationAngles.z,0.0,0.0,1.0);
 		glColor4f(FFilter.r,FFilter.g,FFilter.b, FFilter.a);
		glEnableClientState(GL_VERTEX_ARRAY);
		glVertexPointer(3, GL_FLOAT, 0, 0);
		glDrawElements(GL_QUADS, sizeof(FCubeIndex)/sizeof(unsigned int), GL_UNSIGNED_INT, 0);
		glDisableClientState(GL_VERTEX_ARRAY);
 		glPopMatrix();
 		CRITICAL_SECTION_END();	
 	}
 }