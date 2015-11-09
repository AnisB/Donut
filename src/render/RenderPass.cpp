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
	: m_canvas(nullptr)
	, m_vfx(nullptr)
	, FRenderToTexture(false)
	{
		FCamera = new Camera();
		FRoot = new TNode();
	}
	TRenderPass::~TRenderPass()
	{
		if(m_canvas)
			delete m_canvas;
		if(m_vfx)
			delete m_vfx;
		delete FCamera;
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
			std::vector<TUniformHandler> values;
			TUniformHandler fcoeff;
			fcoeff.SetValue<float>(TShaderData::FLOAT, "fcoef", FCamera->GetFCoeff());
			values.push_back(fcoeff);
			FRoot->Draw(identity, FCamera->GetProjectionMatrix()*FCamera->GetViewMatrix(),values);
			Unbind();
			m_vfx->Draw(m_canvas->Result());
		}
		else
		{
			Matrix4 identity;
			TUniformHandler fcoeff;
			std::vector<TUniformHandler> values;
			fcoeff.SetValue<float>(TShaderData::FLOAT, "fcoef", FCamera->GetFCoeff());
			values.push_back(fcoeff);
			SetIdentity(identity);
			FRoot->Draw(identity, FCamera->GetProjectionMatrix()*FCamera->GetViewMatrix(), values);
		}
	}
	void TRenderPass::Init()
	{
 		//GRAPHICS_DEBUG("Initing the canvas");
		if(FRenderToTexture)
		{
			m_canvas->Init();
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
				drw.UpdateCameraData(FCamera->GetProjectionMatrix(),FCamera->GetViewMatrix());
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
		m_canvas->Enable();
	}

	void TRenderPass::SetShader(const TShader& _shader)
	{
		m_canvas->SetShader(_shader);
		FRenderToTexture = true;
	}

	void TRenderPass::Unbind()
	{
		m_canvas->Disable();
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
		TTexture* texture  = ResourceManager::Instance().FetchTexture(_textureName);
		FFrameCanvas->AttachTexture(texture, _unifomName);
	}
	// END CLASS IMPLEMENTATION


 }
