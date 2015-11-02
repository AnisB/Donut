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

// Library includes
#include "shader.h"
#include "core/Camera.h"

namespace Donut
{
	class TDrawable
	{
	public:
		TDrawable();
		TDrawable(const TShader& _shader);
		virtual ~TDrawable();

		virtual void Draw() = 0;
		virtual void Init() = 0;

		void Bind();
		void Unbind();

		void SetShader(const TShader& _shader);

		virtual void UpdateModelMatrix(const Matrix4& _drawingModelMatrix, const Matrix4& _viewProjectionMatrix);
		void UpdateCameraData(const Matrix4& _projection, const Matrix4& _view);

		const TShader& GetShader()
		{
			return FShader;
		}

	protected:
		virtual void GenerateShader();
	protected:
		TShader FShader;
	};
}
 #endif // DONUT_DRAWABLE_OBJECT