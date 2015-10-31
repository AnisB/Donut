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

 namespace Donut
 {
 class TCubeR : public TDrawableObject, public TThreadSharedObject
 {
 public:
 	TCubeR(const Vector3& _vec, float parDimension, bool _autoInit = true);
 	TCubeR(const Vector3& _vec, float parDimension, const TShader& _shader, bool _autoInit = true);
 	~TCubeR();

 	virtual void UpdateInfoShader();
 	virtual void Init();
 	virtual void Draw();

 	void SetPosition(const Vector3& parPos);

 protected:
 	Vector3 FPosition;
 	float FDimension;

 	// VBO & VAO
 	GLuint FVertexArrayID;
 	GLuint FVBO;
 	GLuint FIBO;
 };
}
 #endif // DONUT_DUBE_R