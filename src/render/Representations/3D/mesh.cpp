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
 #include "Render/Defines.h"
 #include "Render/Const.h"
 #include "Render/Helper.h"
 #include "resource/resourcemanager.h"
 #include "resource/sugarloader.h"
 #include "Base/Common.h"
 #include "MultiThread/Defines.h"
 #include <string.h>


namespace Donut
{
 	TMesh::TMesh(TVec3 parPosition, const std::string& parSugarName)
 	: TDrawableObject()
 	, FPosition(parPosition)
 	, FSugarModel(TSugarLoader::Instance().GetSugar(parSugarName))
 	{
 		FModelMatrix = FModelMatrix*Matrix4::translate(parPosition);
 		FShader.FVertexShader = FSugarModel.shader.vertex;
 		FShader.FTessControl = FSugarModel.shader.tesscontrol;
 		FShader.FTessEval = FSugarModel.shader.tesseval;
 		FShader.FGeometryShader = FSugarModel.shader.geometry;
 		FShader.FFragmentShader = FSugarModel.shader.fragment;
 		ResourceManager::Instance().LoadTextures(FSugarModel);
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
 	}

 	void TMesh::Init()
 	{
 		FModel = ResourceManager::Instance().LoadObj(FShader,FSugarModel.model);
 		Bind();
 		ResourceManager::Instance().LoadSugarData(FShader,FSugarModel);
 		Unbind();

 	}

 	void TMesh::SetPosition(const TVec3& parPos)
 	{
 		// CRITICAL_SECTION_BEGIN();
 		FPosition = parPos;
 		// CRITICAL_SECTION_END();	
 	}

 	void TMesh::UpdateInfoShader(const Matrix4& parModelMatrix, Camera* parCamera)
 	{
		TDrawableObject::UpdateInfoShader(parModelMatrix, parCamera);
 		ShaderManager::Instance().PreDrawSugarData(FSugarModel);
 	}

 	void TMesh::Draw()
 	{	
	  	glBindVertexArray (FModel->vertexArray);
	  	// RENDER_DEBUG("Tesselation active: "<<FSugarModel.shader.isTesselated<<FModel->nbVertices);
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