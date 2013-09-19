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


 #ifndef DONUT_SQUARE
 #define DONUT_SQUARE

#include "Render/DrawableObject.h"
#include "Render/Representations/SquareRepresentation.h"
#include "Math/FloatN.h"

 namespace Donut{
 class TSquare
 {
 public:
 	TSquare(float2 parPosition, float parDimension);
 	~TSquare();

 	void SetPosition(const float2& parPos);

 	void SetPosition(float parX, float parY);

 	void Rotate(float parAngle);

 	const float2& GetPosition();

 	void UpdateRepresentation();

 	TDrawableObject * GetRepresentation();


 protected:
 	float2 FPosition;
 	float FDimension;
 	float FRotation;
 	TSquareRepresentation * FRepresentation;
 };
}
 #endif // DONUT_SQUARE