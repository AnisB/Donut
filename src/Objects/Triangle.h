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
#include "Math/FloatN.h"

 namespace Donut{
 class TTriangle
 {
 public:
 	TTriangle(float2 parA,float2  parB, float2  parC);
 	~TTriangle();


 	void SetPosition(const float2& parX);

 	void Rotate(float parAngle);

 	const float2& GetPosition();

 	void UpdateRepresentation();

 	TDrawableObject * GetRepresentation();


 protected:
 	float2 FPointA;
 	float2 FPointB;
 	float2 FPointC;

 	float2 FCenter;
 	TTriangleRepresentation * FRepresentation;
 };
}
 #endif // DONUT_TRIANGLE