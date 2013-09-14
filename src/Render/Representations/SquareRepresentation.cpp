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


 #include "SquareRepresentation.h"
 #include "Render/Defines.h"
 #include "Base/Common.h"
 #include "MultiThread/Defines.h"


namespace Donut{
 	TSquareRepresentation::TSquareRepresentation(float2 parPosition, float parDimension)
 	: TDrawableObject()
 	, FPosition(parPosition)
 	, FDimension(parDimension)
 	{

 	}
 	TSquareRepresentation::~TSquareRepresentation()
 	{

 	}
 	void TSquareRepresentation::SetPosition(const float2& parPos)
 	{
 		CRITICAL_SECTION_BEGIN();
 		FPosition = parPos;
 		CRITICAL_SECTION_END();	
 	}

 	void TSquareRepresentation::SetPosition(float parX, float parY)
 	{
 		CRITICAL_SECTION_BEGIN();
 		FPosition.x = parX;
 		FPosition.y = parY;
 		CRITICAL_SECTION_END();	
 	}

 	const float2 TSquareRepresentation::GetPosition()
 	{
 		float2 position;
 		CRITICAL_SECTION_BEGIN();
 		position = FPosition;
 		CRITICAL_SECTION_END();	
 		return position;
 	}
 	void TSquareRepresentation::Draw()
 	{
 		glColor4f(FFilter.r,FFilter.g,FFilter.b, FFilter.a);
 		glBegin(GL_QUADS); // Start drawing a quad primitive  
 		glVertex2f(FPosition.x, FPosition.y); // The bottom left corner  
 		glVertex2f(FPosition.x + FDimension, FPosition.y); // The bottom left corner  
 		glVertex2f(FPosition.x + FDimension, FPosition.y + FDimension); // The bottom left corner  
 		glVertex2f(FPosition.x, FPosition.y + FDimension); // The bottom left corner  
 		glEnd(); 
 	}
 }
