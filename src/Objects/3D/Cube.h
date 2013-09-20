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


 #ifndef DONUT_CUBE
 #define DONUT_CUBE

#include "Render/DrawableObject.h"
#include "Render/Representations/3D/CubeR.h"
#include "Math/FloatN.h"

 namespace Donut{
 class TCube
 {
 public:
 	TCube(float3 parPosition, float parDimension);
 	~TCube();

 	void SetPosition(const float3& parPos);

 	void RotateX(float parAngle);
 	void RotateY(float parAngle);
 	void RotateZ(float parAngle);

 	const float3& GetPosition();

 	void UpdateRepresentation();

 	TDrawableObject * GetRepresentation();

 protected:
 	float3 FPosition;
 	float FDimension;
 	float3 FRotation;
 	TCubeR * FRepresentation;
 };
}
 #endif // DONUT_CUBE