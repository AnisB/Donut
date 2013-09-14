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


 #ifndef DONUT_TRIANGLE_REPRESENTATION
 #define DONUT_TRIANGLE_REPRESENTATION

#include "../DrawableObject.h"
#include "MultiThread/ThreadSharedObject.h"
#include "Math/FloatN.h"

 namespace Donut{
 class TTriangleRepresentation : public TDrawableObject, public TThreadSharedObject
 {
 public:
 	TTriangleRepresentation(float2 parA, float2 parB, float2 parC);
 	~TTriangleRepresentation();

 	virtual void Draw();

 	void SetA(const float2& parPos);
 	void SetB(const float2& parPos);
 	void SetC(const float2& parPos);

 protected:
 	float2 FPointA;
 	float2 FPointB;
 	float2 FPointC;
 };
}
 #endif // DONUT_TRIANGLE_REPRESENTATION