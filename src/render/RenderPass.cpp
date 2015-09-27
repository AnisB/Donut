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

#include "Base/Common.h"
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
 		foreach(drawable, FDrawables)
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
			FRoot->Draw(Matrix4(MatrixInit::Identity), FCamera);
			FCamera->ChangeNoticed();
			Unbind();
			FFrameCanvas->Draw(FLights);
		}
		else
		{
			FRoot->Draw(Matrix4(MatrixInit::Identity), FCamera);
			FCamera->ChangeNoticed();
		}
	}
	void TRenderPass::Init()
	{
 		//RENDER_DEBUG("Initing the canvas");
		
		if(FRenderToTexture)
		{
			FFrameCanvas->Init();
		}
		foreach(drawable,FDrawables)
		{
			(*drawable)->GenerateShader();
			(*drawable)->Init();
		}
		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LEQUAL);
 		//RENDER_DEBUG("Canvas created");
	}

	void TRenderPass::PreparePass()
	{
		if(FCamera->HasChanged())
		{
			foreach(drawable,FDrawables)
			{
				TDrawableObject & drw = *(*drawable);
				drw.Bind();
				drw.UpdateCamera(FCamera->GetProjectionMatrix(),FCamera->GetViewMatrix());
				drw.Unbind();
			}
			foreach(light,FLights)
			{	
				TLight & lt = *(*light);
				lt.Bind();
				lt.UpdateCamera(FCamera->GetProjectionMatrix(),FCamera->GetViewMatrix());
				lt.Unbind();
			}
		}
		FCamera->ChangeNoticed();
	}

	void TRenderPass::AddDrawable(TDrawableObject* parDrawable)
	{
		FDrawables.push_back(parDrawable);
 		RENDER_DEBUG("Drawable added "<< FDrawables.size());
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

	void TRenderPass::RemoveDrawable(TDrawableObject* parDrawable)
	{
 		RENDER_DEBUG("Removing drawable");
		FDrawables.remove(parDrawable);
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
		FLights.remove(parLight);
	}

	void TRenderPass::AddTexture(const std::string& _textureName, const std::string& _unifomName)
	{
		TTexture* texture  = ResourceManager::Instance().LoadTexture(_textureName);
		FFrameCanvas->AttachTexture(texture, _unifomName);
	}
	// END CLASS IMPLEMENTATION


 }
