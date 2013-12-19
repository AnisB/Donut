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


 #ifndef DONUT_SQUARE_REPRESENTATION
 #define DONUT_SQUARE_REPRESENTATION

#include "Render/DrawableObject.h"
#include "MultiThread/ThreadSharedObject.h"
#include "Math/vec.h"

 namespace Donut{
 class TSquareRepresentation : public TDrawableObject, public TThreadSharedObject
 {
 public:
 	TSquareRepresentation(TVec2 parPosition, float parDimension);
 	~TSquareRepresentation();

 	virtual void Draw();

 	void SetDimension(float parDimension);
 	void SetPosition(const TVec2& parPos);
 	void SetPosition(float parX, float parY);

 	void SetRotation(float parPos);

 	TVec2 GetPosition();


 protected:
 	TVec2 FPosition;
 	float FDimension;
 	float FRotationAngle;
 };
}
 #endif // DONUT_SQUARE_REPRESENTATION