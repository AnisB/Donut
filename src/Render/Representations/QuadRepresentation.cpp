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


 #include "QuadRepresentation.h"
 #include "Render/Defines.h"
 #include "Base/Common.h"
 #include "MultiThread/Defines.h"


namespace Donut{
 	TQuadRepresentation::TQuadRepresentation(const std::list<TVec2> & parPoints)
 	: FPoints(parPoints)
 	{

 	}
 	TQuadRepresentation::~TQuadRepresentation()
 	{

 	}

 	void TQuadRepresentation::SetPoints(const std::list<TVec2>& parPoints)
 	{
 		CRITICAL_SECTION_BEGIN();
 		FPoints.clear();
 		FPoints = parPoints;
 		CRITICAL_SECTION_END();	
 	}
 	void TQuadRepresentation::Draw()
 	{
 		CRITICAL_SECTION_BEGIN();
 		CRITICAL_SECTION_END();	
 		
 	}
 }
