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
 #include "Render/Helper.h"
 #include "resource/resourcemanager.h"
 #include "resource/sugarloader.h"
 #include "Base/Common.h"
 #include "MultiThread/Defines.h"
 #include <string.h>


namespace Donut
{
 	TMesh::TMesh(const std::string& parSugarName, bool _autoInit)
 	: TDrawable()
 	, FSugarModel(TSugarLoader::Instance().GetSugar(parSugarName))
 	{
 		FShader.FVertexShader = FSugarModel.shader.vertex;
 		FShader.FTessControl = FSugarModel.shader.tesscontrol;
 		FShader.FTessEval = FSugarModel.shader.tesseval;
 		FShader.FGeometryShader = FSugarModel.shader.geometry;
 		FShader.FFragmentShader = FSugarModel.shader.fragment;
 		ResourceManager::Instance().LoadTextures(FSugarModel);
 		if(_autoInit)
 		{
 			Init();
 		}
 	}

	TMesh::TMesh(TShader& _shader, TModel* _model)
 	: TDrawable()
	, FModel(_model)
 	{
 		FShader = _shader;
 	}

 	TMesh::~TMesh()
 	{

 	}

 	void TMesh::AddTexture(TTexture* parTex, const std::string& parName)
 	{
 		TTextureInfo newTex;
		newTex.texID = parTex->FID;
		newTex.index = FSugarModel.textures.size();
		newTex.name = parName;
 		FSugarModel.textures.push_back(newTex);
 		Bind();
 		ShaderManager::Instance().InjectTex(FShader, newTex.texID, newTex.name, newTex.index);
 		Unbind();
 	}

 	void TMesh::Init()
 	{
 		GenerateShader();
 		FModel = ResourceManager::Instance().LoadObj(FShader,FSugarModel.model);
 		Bind();
 		ResourceManager::Instance().LoadSugarData(FShader,FSugarModel);
 		Unbind();

 	}

 	void TMesh::UpdateModelMatrix(const Matrix4& _modelMatrix, const Matrix4& _viewProjectionMatrix)
 	{
		TDrawable::UpdateModelMatrix(_modelMatrix, _viewProjectionMatrix);
		foreach_macro(tex, FSugarModel.textures)
		{
			ShaderManager::Instance().BindTex(tex->texID, tex->index);
		}
 	}

 	void TMesh::Draw()
 	{	
	  	glBindVertexArray (FModel->vertexArray);
	  	if(FSugarModel.shader.isTesselated)
	  	{
	  		glDrawElements(GL_PATCHES, FModel->nbVertices, GL_UNSIGNED_INT, 0);
	  	}
	  	else
	  	{
	  		glDrawElements(GL_TRIANGLES, FModel->nbVertices, GL_UNSIGNED_INT, 0);
	  	}
	  	glBindVertexArray (0);
 	}
 }