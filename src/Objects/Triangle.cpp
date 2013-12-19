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
 	TTriangle::TTriangle(TVec2 parA, TVec2 parB,TVec2 parC)
 	: FPointA(parA)
 	, FPointB(parB)
 	, FPointC(parC)
 	, FRotation(0)
 	{
 		FCenter.val[0] = (FPointA.val[0] + FPointB.val[0] + FPointC.val[0])/3;
 		FCenter.val[1] = (FPointA.val[1] + FPointB.val[1]+ FPointC.val[1])/3;
 		FRepresentation = new TTriangleRepresentation(parA-FCenter, parB-FCenter, parC-FCenter, FCenter);
 	}
 	TTriangle::~TTriangle()
 	{
 		delete FRepresentation;
 	}

 	void TTriangle::SetPosition(const TVec2& parPos)
 	{
 		TVec2 diffPos = (parPos - FCenter);
 		FPointA += diffPos;
 		FPointB += diffPos;
 		FPointC += diffPos;
 		UpdateRepresentation();
 	}

 	void TTriangle::Rotate(float parAngle)
 	{
 		FRotation += parAngle;
 		FRotation = fmod(FRotation, 360.0);
 		UpdateRepresentation();
 	}

 	const TVec2& TTriangle::GetPosition()
 	{
 		return FCenter;
 	}

 	void TTriangle::UpdateRepresentation()
 	{
 		if( FRepresentation != NULL)
 		{
	 		FRepresentation->SetA(FPointA-FCenter);
	 		FRepresentation->SetB(FPointB-FCenter);
	 		FRepresentation->SetC(FPointC-FCenter);
	 		FRepresentation->SetCenter(FCenter);
	 		FRepresentation->SetRotation(FRotation);
	 	}
 	}

 	TDrawableObject * TTriangle::GetRepresentation()
 	{
 		return FRepresentation;
 	}

 }
