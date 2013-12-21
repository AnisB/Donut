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
 #include <Base/DebugPrinters.h>
 #include "Defines.h"
 #include "ShaderManager.h"

namespace Donut{
 	TDrawableObject::TDrawableObject()
 	: FFilter(1.0f,1.0f,1.0f,1.0f)
 	, FShader(0,BASIC_VERTEX_SHADER,BASIC_FRAGMENT_SHADER)
 	, FModelMatrix(MatrixInit::Identity)
 	{
 	}
 	TDrawableObject::~TDrawableObject()
 	{

 	}

 	void TDrawableObject::Bind()
 	{
 		//RENDER_DEBUG("Biding dude "<<FShader.FActive);
 		if(FShader.FActive)
 		{
 			//RENDER_DEBUG("I bind");
 			ShaderManager::Instance().EnableShader(FShader);
 		}
 	}
 	void TDrawableObject::UpdateInfoShader()
 	{
		ShaderManager::Instance().InjectMat4(FShader,FModelMatrix,"model");
 	}
 	void TDrawableObject::Unbind()
 	{
 		if(FShader.FActive)
 		{
 			ShaderManager::Instance().DisableShader();
 		}
 	}

 	void TDrawableObject::SetVertexShader(const std::string& parShaderPath)
 	{
 		FShader.FVertexShader = parShaderPath;
 		FShader.FActive = true;
 	}

 	void TDrawableObject::SetFragmentShader(const std::string& parShaderPath)
 	{
 		FShader.FFragmentShader = parShaderPath;
 		FShader.FActive = true;
 	}

 	void TDrawableObject::GenerateShader()
 	{
		//RENDER_DEBUG("generation");
		FShader = ShaderManager::Instance().CreateShader(FShader.FVertexShader, FShader.FFragmentShader);
 	}
 }
