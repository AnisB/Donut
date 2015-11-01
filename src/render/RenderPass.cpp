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

#include "RenderPass.h"
#include "graphics/common.h"
#include "base/Common.h"
#include "MultiThread/Defines.h"
#include "Base/Macro.h"
#include "resource/resourcemanager.h"

 namespace Donut
 {

 	//CLASS IMPLEMENTATION
	TRenderPass::TRenderPass()
	{
		FRenderToTexture = false;
		FFrameCanvas = new TFrameCanvas();
		FCamera = new Camera();
		FRoot = new TNode();
	}
	TRenderPass::~TRenderPass()
	{
		delete FCamera;
		delete FFrameCanvas;
		delete FRoot;
 		foreach_macro(drawable, FDrawables)
 		{
 			if(*drawable)
 				delete *drawable;
 		}
	}

	TNode* TRenderPass::GetRoot()
	{
		return FRoot;
	}

	void TRenderPass::Draw()
	{
		PreparePass();
		if(FRenderToTexture)
		{
			Bind();
			Matrix4 identity;
			SetIdentity(identity);
			FRoot->Draw(identity, FCamera->GetProjectionMatrix()*FCamera->GetViewMatrix());
			Unbind();
			FFrameCanvas->Draw(FLights);
		}
		else
		{
			Matrix4 identity;
			SetIdentity(identity);
			FRoot->Draw(identity, FCamera->GetProjectionMatrix()*FCamera->GetViewMatrix());
		}
	}
	void TRenderPass::Init()
	{
 		//GRAPHICS_DEBUG("Initing the canvas");
		
		if(FRenderToTexture)
		{
			FFrameCanvas->Init();
		}
		foreach_macro(drawable,FDrawables)
		{
			(*drawable)->Init();
		}
		
		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LEQUAL);
 		//GRAPHICS_DEBUG("Canvas created");
	}

	void TRenderPass::PreparePass()
	{
		if(FCamera->HasChanged())
		{
			foreach_macro(drawable,FDrawables)
			{
				TDrawable & drw = *(*drawable);
				drw.Bind();
				drw.UpdateCameraData(FCamera->GetProjectionMatrix(),FCamera->GetViewMatrix());
				drw.Unbind();
			}
			foreach_macro(light,FLights)
			{	
				TLight & lt = *(*light);
				lt.Bind();
				lt.UpdateCamera(FCamera->GetProjectionMatrix(),FCamera->GetViewMatrix());
				lt.Unbind();
			}
			FCamera->ChangeNoticed();
		}
	}

	void TRenderPass::AddDrawable(TDrawable* parDrawable)
	{
		FDrawables.push_back(parDrawable);
 		GRAPHICS_DEBUG("TDrawable added "<< FDrawables.size());
	}

	void TRenderPass::Bind()
	{
		FFrameCanvas->Enable();
	}

	void TRenderPass::SetFragmentShader(const std::string& parFragShader)
	{
		FFrameCanvas->SetFragmentShader(parFragShader);
		FRenderToTexture = true;
	}

	void TRenderPass::SetVertexShader(const std::string& parFragShader)
	{
		FFrameCanvas->SetVertexShader(parFragShader);
		FRenderToTexture = true;
	}

	void TRenderPass::Unbind()
	{
		FFrameCanvas->Disable();
	}

	void TRenderPass::RemoveDrawable(TDrawable* _drawable)
	{
		GRAPHICS_DEBUG("Maybe you should not call this function, preferably disabled");
		auto drwblIT = std::find(FDrawables.begin(), FDrawables.end(), _drawable);
		ASSERT(drwblIT != FDrawables.end());
		if(drwblIT != FDrawables.end())
		{
			FDrawables.erase(drwblIT);
		}
	}
	void TRenderPass::SetRenderType(FrameCanvasContent::Type parType)
	{
		FFrameCanvas->SetType(parType);
		FRenderToTexture = true;
	}
	void TRenderPass::Clear()
	{
		CRITICAL_SECTION_BEGIN();
		FDrawables.clear();
		CRITICAL_SECTION_END();
	}

	void TRenderPass::AddLight(TLight* parLight)
	{
		FLights.push_back(parLight);
		FFrameCanvas->InjectData(parLight->GetShader());

	}
	void TRenderPass::RemoveLight(TLight* parLight)
	{
		ASSERT_NOT_IMPLEMENTED();
		//FLights.erase(parLight);
	}

	void TRenderPass::AddTexture(const std::string& _textureName, const std::string& _unifomName)
	{
		TTexture* texture  = ResourceManager::Instance().LoadTexture(_textureName);
		FFrameCanvas->AttachTexture(texture, _unifomName);
	}
	// END CLASS IMPLEMENTATION


 }
