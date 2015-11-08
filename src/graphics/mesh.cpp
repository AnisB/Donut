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


 #include "Mesh.h"
 #include "resource/resourcemanager.h"
 #include "resource/sugarloader.h"
 #include "Base/Common.h"
 #include "MultiThread/Defines.h"
 #include <string.h>


namespace Donut
{
	TMesh::TMesh(TMaterial& _material, TGeometry* _geometry)
 	: TDrawable()
	, FGeometry(_geometry)
	, FMaterial(_material)
 	{
 	}

 	TMesh::~TMesh()
 	{

 	}

 	void TMesh::AddTexture(TTexture* parTex, const std::string& parName)
 	{
 		TTextureInfo newTex;
		newTex.texID = parTex->FID;
		newTex.offset = (int)FMaterial.textures.size();
		newTex.name = parName;
 		FMaterial.textures.push_back(newTex);
 	}
 	void TMesh::Draw(const Matrix4& _drawingModelMatrix, const Matrix4& _viewProjectionMatrix, const std::vector<TUniformHandler>& _handlers)
 	{	
 		Bind();
 		ResourceManager::Instance().BindMaterial(FMaterial.shader, FMaterial);
 		foreach_macro(uniform, _handlers)
 		{
 			uniform->Inject(FMaterial.shader);
 		}
 		ShaderManager::Instance().Inject<Matrix4>(FMaterial.shader,_drawingModelMatrix,"model");
		ShaderManager::Instance().Inject<Matrix4>(FMaterial.shader, _viewProjectionMatrix * _drawingModelMatrix,"modelviewprojection");
	  	FGeometry->Draw(FMaterial.shader.FIsTesselated);
 		Unbind();
 	}

	void TMesh::UpdateCameraData(const Matrix4& _projection, const Matrix4& _view)
	{
 		Bind();
		ShaderManager::Instance().Inject<Matrix4>(FMaterial.shader, _view,"view");
		ShaderManager::Instance().Inject<Matrix4>(FMaterial.shader, _projection,"projection");
 		Unbind();
	}

	void TMesh::Bind()
	{
		ASSERT_NO_RELEASE(FMaterial.shader.IsActive());
		ShaderManager::Instance().EnableShader(FMaterial.shader);
	}

	void TMesh::Unbind()
	{
		ASSERT_NO_RELEASE(FMaterial.shader.IsActive());
		ShaderManager::Instance().DisableShader();
	}
 }