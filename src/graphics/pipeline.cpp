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


// Library includes
#include "pipeline.h"
#include "resource/pipelineloader.h"
// Canvas
#include "emptycanvas.h"
#include "simplecanvas.h"
#include "effectcanvas.h"
#include "gbuffercanvas.h"
// FX
#include "vfxpass.h"
#include "simplefx.h"
#include "defferedfx.h"
#include "environmentfx.h"
#include "skyboxfx.h"
// Other
#include "base/macro.h"
#include "resource/resourcemanager.h"
#include "geometrypass.h"

namespace Donut
{
	TPipeline::TPipeline()
	{
		camera = new Camera();
	}

	TPipeline::~TPipeline()
	{
		foreach_macro(passIT, passes)
		{
			delete *passIT;
		}
		delete camera;
	}

	void TPipeline::BuildPipelineData()
	{
		foreach_macro(pass, passes)
		{
			TPass* currentPass = *pass;
			const TBufferOutput* bufferOutput =  currentPass->GetOutput();
			foreach_macro(buf, bufferOutput->buffers)
			{
				TTextureInfo newTex;
				newTex.texID = buf->texID;
				newTex.offset = (int)pipelineData.buffers.size();
				newTex.name = buf->name;
				pipelineData.buffers.push_back(newTex);
			}				
		}
	}

	TPipeline* GenerateGraphicPipeline(TFlour* _scene, int _width, int _height)
	{
		// Creating the pipeline
		TPipeline* pipeline = new TPipeline();
		// Fetching its internal data
		pipeline->pipelineData.width = _width;
		pipeline->pipelineData.height = _height;
		Camera* camera =  pipeline->camera;
		TBufferOutput& buffers =  pipeline->pipelineData;


		// Fetch the pipeline that was specified
		const TPipelineDescriptor& pipelineDesc = TPipelineLoader::Instance().FetchPipeline(_scene->pipelineName);
		GRAPHICS_INFO("Creating pipeline "<<pipelineDesc.name);

		foreach_macro(pass, pipelineDesc.passes)
		{
			// Fetching the pointers
			if(pass->tag == TPassTag::GEOMETRY)
			{
				const TPipelineCanvas& canvasDesc = pass->canvas;
				TCanvas* canvas = nullptr;
				switch(canvasDesc.tag)
				{
					case TCanvasTag::EMPTY:
					{
						canvas = new TEmptyCanvas(_width, _height);
					}
					break;
					case TCanvasTag::EFFECT:
					{
						canvas = new TEffectCanvas(_width, _height, canvasDesc.output);
					}
					break;
					case TCanvasTag::GBUFFER:
					{
						canvas = new TGBufferCanvas(_width, _height);
					}
					break;
					default:
					ASSERT_FAIL_MSG("Unexisting canvas type");
					break;
				}

				TGeometryPass* geometryPass = new TGeometryPass(canvas, _scene);
				geometryPass->SetCamera(camera);
				pipeline->passes.push_back(geometryPass);

			}
			else if (pass->tag == TPassTag::VFX)
			{
				const TPipelineCanvas& canvasDesc = pass->canvas;
				TCanvas* canvas = nullptr;
				switch(canvasDesc.tag)
				{
					case TCanvasTag::EMPTY:
					{
						canvas = new TEmptyCanvas(_width, _height);
					}
					break;
					case TCanvasTag::EFFECT:
					{
						canvas = new TEffectCanvas(_width, _height, canvasDesc.output);
					}
					break;
					case TCanvasTag::GBUFFER:
					{
						canvas = new TGBufferCanvas(_width, _height);
					}
					break;
					default:
					ASSERT_FAIL_MSG("Unexisting canvas type");
					break;
				}

				const TPipelineVFX& vfxDescriptor = pass->vfx;
				TVFX* vfx = nullptr;
				switch(vfxDescriptor.tag)
				{
					case TVFXTag::SIMPLEFX:
					{
						TSimpleFX* sfx = new TSimpleFX(vfxDescriptor.shader);
						vfx = sfx;
					}
					break;
					case TVFXTag::ENVIRONEMENT:
					{
						if(_scene->sh)
						{
							TEnvironmentFX* envFX = new TEnvironmentFX();
							envFX->SetSH(_scene->sh);
							vfx = envFX;
						}
					}
					break;
					case TVFXTag::DEFFERED:
					{
						TDefferedFX* deffered = new TDefferedFX();
						deffered->SetLights(_scene->lights);
						vfx = deffered;
					}
					break;
					case TVFXTag::SKYBOX:
					{
						TSkyboxFX* skyboxFX = new TSkyboxFX(vfxDescriptor.shader);
						skyboxFX->SetSkybox(_scene->skybox);
						skyboxFX->SetCamera(camera);
						vfx = skyboxFX;
					}
					break;
					default:
					ASSERT_FAIL_MSG("Unexisting fx type");
					break;
				}

				ASSERT_POINTER_NOT_NULL_NO_RELEASE(vfx);
				foreach_macro(tex2D, vfxDescriptor.textures)
				{
					vfx->AddTexture(ResourceManager::Instance().FetchTexture(tex2D->file), tex2D->name);
				}

				TVFXPass* vfxPass = new TVFXPass(canvas, vfx);
				vfxPass->SetCamera(camera);
				pipeline->passes.push_back(vfxPass);
			}
			else
			{
				ASSERT_FAIL_MSG("Unexisting pass type");
			}
		}
		return pipeline;
	}

}