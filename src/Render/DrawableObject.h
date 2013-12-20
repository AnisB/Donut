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
namespace Donut
{
 class TDrawableObject
 {
 public:
 	TDrawableObject();
 	virtual ~TDrawableObject();

 	virtual void Draw() = 0;
 	virtual void Init()
 	{

 	}
 	
 	void Bind();
 	void Unbind();

 	virtual void GenerateShader();
 	void SetVertexShader(const std::string& parShaderPath);
 	void SetFragmentShader(const std::string& parShaderPath);
 	void InjectModelMatrix();
 	const Matrix4& GetModelMatrix() {return FModelMatrix;}

 	virtual void SetColor(const TColorFilter& parFilter)
 	{
 		FFilter = parFilter;
 	}
 	const TShader& GetShader()
 	{
 		return FShader;
 	}

 public:
 	TColorFilter FFilter;
 	TShader FShader;
 	Matrix4 FModelMatrix;
 };
}
 #endif // DONUT_DRAWABLE_OBJECT