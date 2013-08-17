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

#include "DrawableObject.h"
#include "Math/FloatN.h"

 namespace Donut{
 class TSquare : public TDrawableObject
 {
 public:
 	TSquare(float2 parPosition, float parDimension);
 	~TSquare();

 	virtual void Draw();

 	void SetPosition(const float2& parPos)
 	{
 		FPosition = parPos;
 	}

 	void SetPosition(float parX, float parY)
 	{
 		FPosition.x = parX;
 		FPosition.y = parY;
 	}

 	const float2& GetPosition()
 	{
 		return FPosition;
 	}


 protected:
 	float2 FPosition;
 	float FDimension;
 };
}
 #endif // DONUT_SQUARE