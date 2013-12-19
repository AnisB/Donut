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
 	TTriangleRepresentation::TTriangleRepresentation(const TVec2& parA, const TVec2& parB, const TVec2& parC, const TVec2& parCenter)
 	: FPointA(parA)
 	, FPointB(parB)
 	, FPointC(parC)
 	, FCenter(parCenter)
 	, FRotation(0)
 	{

 	}
 	TTriangleRepresentation::~TTriangleRepresentation()
 	{

 	}

 	void TTriangleRepresentation::SetA(const TVec2& parPos)
 	{
 		CRITICAL_SECTION_BEGIN();
 		FPointA = parPos;
 		CRITICAL_SECTION_END();	
 	}

 	void TTriangleRepresentation::SetB(const TVec2& parPos)
 	{
 		CRITICAL_SECTION_BEGIN();
 		FPointB = parPos;
 		CRITICAL_SECTION_END();	
 	}

 	void TTriangleRepresentation::SetC(const TVec2& parPos)
 	{
 		CRITICAL_SECTION_BEGIN();
 		FPointC = parPos;
 		CRITICAL_SECTION_END();	
 	}

 	void TTriangleRepresentation::SetCenter(const TVec2& parPos)
 	{
 		CRITICAL_SECTION_BEGIN();
 		FCenter = parPos;
 		CRITICAL_SECTION_END();	
 	}


 	void TTriangleRepresentation::SetRotation(float parRotation)
 	{
 		CRITICAL_SECTION_BEGIN();
 		FRotation = parRotation;
 		CRITICAL_SECTION_END();	
 	}

 	void TTriangleRepresentation::Draw()
 	{
 		CRITICAL_SECTION_BEGIN();
 		CRITICAL_SECTION_END();		
 	}
 }
