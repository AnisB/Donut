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


 #include "Quad.h"
 #include "Render/Defines.h"
 #include "Base/Common.h"


namespace Donut{
 	TQuad::TQuad(const std::list<float2> & parPoints)
 	: FPoints(parPoints)
 	{
 		float sumX = 0, sumY = 0;
 		foreach(point, FPoints)
 		{
 			sumX += point->x; 
 			sumY += point->y; 
 		}
 		FCenter.x = (sumX)/parPoints.size();
 		FCenter.y = (sumY)/parPoints.size();
 		FRepresentation = new TQuadRepresentation(parPoints);
 	}
 	TQuad::~TQuad()
 	{
 		delete FRepresentation;
 	}

 	void TQuad::SetPosition(const float2& parPos)
 	{
 		float2 diffPos = (parPos - FCenter);
 		foreach(point, FPoints)
 		{
 			(*point) += diffPos; 
 		}
 		UpdateRepresentation();
 	}

 	void TQuad::Rotate(float parAngle)
 	{
 		if(parAngle > 0)
 		{

 		}
 	}

 	const float2& TQuad::GetPosition()
 	{
 		return FCenter;
 	}

 	void TQuad::UpdateRepresentation()
 	{
 		FRepresentation->SetPoints(FPoints);
 	}

 	TDrawableObject * TQuad::GetRepresentation()
 	{
 		return FRepresentation;
 	}

 }
