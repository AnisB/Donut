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


 #include "DrawableObject.h"
 #include <Base/Common.h>
 #include "Defines.h"
 #include "ShaderManager.h"

namespace Donut{
 	TDrawableObject::TDrawableObject()
 	: FShader(0,BASIC_SHADER, BASIC_SHADER, BASIC_SHADER, BASIC_SHADER, BASIC_SHADER)
 	, FModelMatrix()
 	{
 		matrix4(FModelMatrix, MatrixInit::Identity);
 	}
 	
  	TDrawableObject::TDrawableObject(const TShader& _shader)
 	: FShader(_shader)
 	, FModelMatrix()
 	{
 		matrix4(FModelMatrix, MatrixInit::Identity);
 	}

 	TDrawableObject::~TDrawableObject()
 	{

 	}

 	void TDrawableObject::Bind()
 	{
 		ASSERT_NO_RELEASE(FShader.FActive);
		ShaderManager::Instance().EnableShader(FShader);
 	}
 	void TDrawableObject::UpdateInfoShader(const Matrix4& parModelMatrix, Camera* parCamera)
 	{
 		const Matrix4& reftmpMult = FModelMatrix*parModelMatrix;
		ShaderManager::Instance().InjectMat4(FShader,reftmpMult,"model");
		ShaderManager::Instance().InjectMat4(FShader,parCamera->GetProjectionMatrix()*parCamera->GetViewMatrix()*reftmpMult,"modelviewprojection");
 	}

 	void TDrawableObject::UpdateCamera(const Matrix4& parProjection, const Matrix4& parView)
 	{
		ShaderManager::Instance().InjectMat4(FShader,parView,"view");
		ShaderManager::Instance().InjectMat4(FShader,parProjection,"projection");
 	}

 	void TDrawableObject::Unbind()
 	{
 		ASSERT_NO_RELEASE(FShader.FActive);
		ShaderManager::Instance().DisableShader();
	}
 	
 	void TDrawableObject::SetShader(const TShader& _shader)
 	{
 		// TODO: Remove one reference from the previous shader in the shader manager
 		FShader = _shader;
 		if(!FShader.FActive)
 		{
 			ShaderManager::Instance().CreateShader(FShader);
 		}
 	}

 	void TDrawableObject::GenerateShader()
 	{
		//RENDER_DEBUG("generation");
		ShaderManager::Instance().CreateShader(FShader);
 	}
 }
