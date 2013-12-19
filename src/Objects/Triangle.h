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


 #ifndef DONUT_TRIANGLE
 #define DONUT_TRIANGLE

#include "Render/DrawableObject.h"
#include "Render/Representations/TriangleRepresentation.h"
#include "Math/vec.h"

 namespace Donut{
 class TTriangle
 {
 public:
 	TTriangle(TVec2 parA,TVec2  parB, TVec2  parC);
 	~TTriangle();


 	void SetPosition(const TVec2& parX);

 	void Rotate(float parAngle);

 	const TVec2& GetPosition();

 	void UpdateRepresentation();

 	TDrawableObject * GetRepresentation();


 protected:
 	TVec2 FPointA;
 	TVec2 FPointB;
 	TVec2 FPointC;

 	TVec2 FCenter;
 	float FRotation;
 	TTriangleRepresentation * FRepresentation;
 };
}
 #endif // DONUT_TRIANGLE