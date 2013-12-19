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


 #include "Square.h"
 #include "Render/Defines.h"
 #include "Base/Common.h"
 #include <math.h>

namespace Donut{
 	TSquare::TSquare(TVec2 parPosition, float parDimension)
 	: FPosition(parPosition)
 	, FDimension(parDimension)
 	, FRotation(0)
 	{
 		FRepresentation = new TSquareRepresentation(parPosition, parDimension);
 	}
 	TSquare::~TSquare()
 	{
 		delete FRepresentation;
 	}

 	void TSquare::SetPosition(const TVec2& parPos)
 	{
 		FPosition = parPos;
 		UpdateRepresentation();
 	}

 	void TSquare::SetVertexShader(const std::string& parVertex)
 	{
 		FRepresentation->SetVertexShader(parVertex);
 	}

 	void TSquare::SetFragmentShader(const std::string& parVertex)
 	{
 		FRepresentation->SetFragmentShader(parVertex);
 	}

 	void TSquare::Rotate(float parAngle)
 	{
 		FRotation += parAngle; 
 		FRotation = fmod(FRotation, 360);
 		UpdateRepresentation();
 	}

 	void TSquare::SetColor(const TColorFilter& parColorFilter)
 	{
 		FRepresentation->SetColor(parColorFilter);
 	}

 	TVec2 TSquare::GetPosition()
 	{
 		return FPosition;
 	}

 	void TSquare::UpdateRepresentation()
 	{
 		if( FRepresentation != NULL)
 		{
 			FRepresentation->SetPosition(FPosition);
 			FRepresentation->SetRotation(FRotation);
 		 	FRepresentation->SetDimension(FDimension);
 		}
 	}

 	TDrawableObject * TSquare::GetRepresentation()
 	{
 		return FRepresentation;
 	}

 }
