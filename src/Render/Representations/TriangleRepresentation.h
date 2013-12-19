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
#include "Math/vec.h"

 namespace Donut{
 class TTriangleRepresentation : public TDrawableObject, public TThreadSharedObject
 {
 public:
 	TTriangleRepresentation(const TVec2& parA, const TVec2& parB, const TVec2& parC, const TVec2& parCenter);
 	~TTriangleRepresentation();

 	virtual void Draw();

 	void SetA(const TVec2& parPos);
 	void SetB(const TVec2& parPos);
 	void SetC(const TVec2& parPos);
 	void SetCenter(const TVec2& parPos);

 	void SetRotation(float parRotation);

 protected:
 	TVec2 FPointA;
 	TVec2 FPointB;
 	TVec2 FPointC;
 	TVec2 FCenter;
 	float FRotation;
 };
}
 #endif // DONUT_TRIANGLE_REPRESENTATION