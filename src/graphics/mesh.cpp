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
 	void TMesh::Draw(std::map<std::string, TUniformHandler>& _values, const TBufferOutput& _previousData)
 	{	
 		Bind();
		const Matrix4& model = _values["model"].GetValue<Matrix4>();
		const Matrix4& viewprojection = _values["viewprojection"].GetValue<Matrix4>();
 		ResourceManager::Instance().BindMaterial(FMaterial.shader, FMaterial);
 		foreach_macro(uniform, _values)
 		{
 			uniform->second.Inject(FMaterial.shader);
 		}
		ShaderManager::Instance().Inject<Matrix4>(FMaterial.shader, viewprojection * model,"modelviewprojection");
	  	FGeometry->Draw(FMaterial.shader.FIsTesselated);
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