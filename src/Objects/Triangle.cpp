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


 #include "Triangle.h"
 #include "Render/Defines.h"
 #include "Base/Common.h"


namespace Donut{
 	TTriangle::TTriangle(float2 parA, float2 parB,float2 parC)
 	: FPointA(parA)
 	, FPointB(parB)
 	, FPointC(parC)
 	{
 		FCenter.x = (FPointA.x + FPointB.x + FPointC.x)/3;
 		FCenter.y = (FPointA.y + FPointB.y + FPointC.y)/3;
 		FRepresentation = new TTriangleRepresentation(parA, parB, parC);
 	}
 	TTriangle::~TTriangle()
 	{
 		delete FRepresentation;
 	}

 	void TTriangle::SetPosition(const float2& parPos)
 	{
 		float2 diffPos = (parPos - FCenter);
 		FPointA += diffPos;
 		FPointB += diffPos;
 		FPointC += diffPos;
 		UpdateRepresentation();
 	}

 	void TTriangle::Rotate(float parAngle)
 	{
 		if(parAngle > 0)
 		{

 		}
 	}

 	const float2& TTriangle::GetPosition()
 	{
 		return FCenter;
 	}

 	void TTriangle::UpdateRepresentation()
 	{
 		FRepresentation->SetA(FPointA);
 		FRepresentation->SetB(FPointB);
 		FRepresentation->SetC(FPointC);
 	}

 	TDrawableObject * TTriangle::GetRepresentation()
 	{
 		return FRepresentation;
 	}

 }
