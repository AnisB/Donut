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


 #include "TriangleRepresentation.h"
 #include "Render/Defines.h"
 #include "Base/Common.h"
 #include "MultiThread/Defines.h"


namespace Donut{
 	TTriangleRepresentation::TTriangleRepresentation(float2 parA, float2 parB, float2 parC)
 	: FPointA(parA)
 	, FPointB(parB)
 	, FPointC(parC)
 	{

 	}
 	TTriangleRepresentation::~TTriangleRepresentation()
 	{

 	}

 	void TTriangleRepresentation::SetA(const float2& parPos)
 	{
 		CRITICAL_SECTION_BEGIN();
 		FPointA = parPos;
 		CRITICAL_SECTION_END();	
 	}

 	void TTriangleRepresentation::SetB(const float2& parPos)
 	{
 		CRITICAL_SECTION_BEGIN();
 		FPointB = parPos;
 		CRITICAL_SECTION_END();	
 	}

 	void TTriangleRepresentation::SetC(const float2& parPos)
 	{
 		CRITICAL_SECTION_BEGIN();
 		FPointC = parPos;
 		CRITICAL_SECTION_END();	
 	}

 	void TTriangleRepresentation::Draw()
 	{
 		glColor4f(FFilter.r,FFilter.g,FFilter.b, FFilter.a);
 		glBegin(GL_TRIANGLES); // Start drawing a quad primitive  
 		glVertex2f(FPointA.x, FPointA.y); // The bottom left corner  
 		glVertex2f(FPointB.x , FPointB.y); // The bottom left corner  
 		glVertex2f(FPointC.x , FPointC.y ); // The bottom left corner  
 		glEnd(); 
 	}
 }
