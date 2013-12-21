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


 #ifndef DONUT_DRAWABLE_OBJECT
 #define DONUT_DRAWABLE_OBJECT

#include "Defines.h"
#include "ShaderManager.h"
#include "Camera.h"
namespace Donut
{
 class TDrawableObject
 {
 public:
 	TDrawableObject();
 	virtual ~TDrawableObject();

 	virtual void Draw() = 0;
 	virtual void Init() = 0;

 	void Bind();
 	void Unbind();

 	virtual void GenerateShader();
 	void SetVertexShader(const std::string& parShaderPath);
 	void SetFragmentShader(const std::string& parShaderPath);

 	virtual void UpdateInfoShader(const Matrix4& parModelMatrix, Camera* parCamera);
 	virtual void UpdateCamera(const Matrix4& parProjection, const Matrix4& parView);
 	
 	const Matrix4& GetModelMatrix() {return FModelMatrix;}

 	const TShader& GetShader()
 	{
 		return FShader;
 	}

 public:
 	TShader FShader;
 	Matrix4 FModelMatrix;
 };
}
 #endif // DONUT_DRAWABLE_OBJECT