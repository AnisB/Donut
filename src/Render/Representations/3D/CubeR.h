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


 #ifndef DONUT_DUBE_R
 #define DONUT_DUBE_R

#include "Render/DrawableObject.h"
#include "MultiThread/ThreadSharedObject.h"
#include "Math/FloatN.h"

 namespace Donut
 {
 class TCubeR : public TDrawableObject, public TThreadSharedObject
 {
 public:
 	TCubeR(float3 parPosition, float parDimension);
 	~TCubeR();

 	virtual void Init();
 	virtual void Draw();

 	void SetPosition(const float3& parPos);

 	void SetRotation(const float3& parRotation);

 protected:
 	float3 FPosition;
 	float FDimension;
 	float3 FRotationAngles;

 	// VBO & IBO
 	GLuint FVBO;
 	GLuint FIBO;
 	float * FCubeVertex;
 	unsigned int * FCubeIndex;
 };
}
 #endif // DONUT_DUBE_R