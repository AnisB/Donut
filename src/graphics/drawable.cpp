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


 #include "drawable.h"
 #include <Base/Common.h>
 #include "ShaderManager.h"

namespace Donut
{
	TDrawable::TDrawable()
	: FShader()
	, FModelMatrix()
	{
		matrix4(FModelMatrix, MatrixInit::Identity);
	}

	TDrawable::TDrawable(const TShader& _shader)
	: FShader(_shader)
	, FModelMatrix()
	{
		matrix4(FModelMatrix, MatrixInit::Identity);
	}

	TDrawable::~TDrawable()
	{

	}

	void TDrawable::Bind()
	{
		ASSERT_NO_RELEASE(FShader.IsActive());
		ShaderManager::Instance().EnableShader(FShader);
	}

	// Update model
	void TDrawable::UpdateModelMatrix(const Matrix4& _drawingModelMatrix, const Matrix4& _viewProjectionMatrix)
	{
		Set(FModelMatrix, _drawingModelMatrix);
		ShaderManager::Instance().InjectMat4(FShader,FModelMatrix,"model");
		ShaderManager::Instance().InjectMat4(FShader, _viewProjectionMatrix * FModelMatrix,"modelviewprojection");
	}

	void TDrawable::UpdateCameraData(const Matrix4& _projection, const Matrix4& _view)
	{
		ShaderManager::Instance().InjectMat4(FShader, _view,"view");
		ShaderManager::Instance().InjectMat4(FShader, _projection,"projection");
		ShaderManager::Instance().InjectMat4(FShader, _projection * _view * FModelMatrix,"modelviewprojection");
	}

	void TDrawable::Unbind()
	{
		ASSERT_NO_RELEASE(FShader.IsActive());
		ShaderManager::Instance().DisableShader();
	}

	void TDrawable::SetShader(const TShader& _shader)
	{
		// TODO: Remove one reference from the previous shader in the shader manager
		FShader = _shader;
		if(!FShader.IsActive())
		{
			GenerateShader();
		}
	}

	void TDrawable::GenerateShader()
	{
		ShaderManager::Instance().CreateShader(FShader);
	}
}
