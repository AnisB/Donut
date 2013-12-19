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
 	TSquareRepresentation::TSquareRepresentation(TVec2 parPosition, float parDimension)
 	: TDrawableObject()
 	, FPosition(parPosition)
 	, FDimension(parDimension)
 	, FRotationAngle(0)
 	{

 	}
 	TSquareRepresentation::~TSquareRepresentation()
 	{

 	}
 	void TSquareRepresentation::SetPosition(const TVec2& parPos)
 	{
 		CRITICAL_SECTION_BEGIN();
 		FPosition = parPos;
 		CRITICAL_SECTION_END();	
 	}

 	void TSquareRepresentation::SetDimension(float parDimension)
 	{
 		CRITICAL_SECTION_BEGIN();
 		FDimension = parDimension;
 		CRITICAL_SECTION_END();	
 	}

 	void TSquareRepresentation::SetPosition(float parX, float parY)
 	{
 		CRITICAL_SECTION_BEGIN();
 		FPosition.val[0] = parX;
 		FPosition.val[1] = parY;
 		CRITICAL_SECTION_END();	
 	}
 	void TSquareRepresentation::SetRotation(float parAngle)
 	{
 		FRotationAngle = parAngle;
 	}
 	TVec2 TSquareRepresentation::GetPosition()
 	{
 		TVec2 position;
 		CRITICAL_SECTION_BEGIN();
 		position = FPosition;
 		CRITICAL_SECTION_END();	
 		return position;
 	}
 	void TSquareRepresentation::Draw()
 	{
 		CRITICAL_SECTION_BEGIN();
 		CRITICAL_SECTION_END();	
 	}
 }
