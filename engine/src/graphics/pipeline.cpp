// Bento includes
#include <bento_base/security.h>

// Library includes
#include "graphics/pipeline.h"
#include "resource/pipeline_descriptor.h"
// Canvas
#include "graphics/emptycanvas.h"
#include "graphics/simplecanvas.h"
#include "graphics/effectcanvas.h"
#include "graphics/gbuffercanvas.h"
// FX
#include "graphics/vfxpass.h"
#include "graphics/simplefx.h"
#include "graphics/defferedfx.h"
#include "graphics/environmentfx.h"
#include "graphics/skyboxfx.h"
// Other
#include "resource/resource_manager.h"
#include "graphics/geometrypass.h"

namespace donut
{
	TPipeline::TPipeline()
	{
		camera = new Camera();
	}

	TPipeline::~TPipeline()
	{
		for(auto& pass : passes)
		{
			delete pass;
		}
		delete camera;
	}

	void TPipeline::BuildPipelineData()
	{
		for(auto& pass : passes)
		{
			const TBufferOutput* bufferOutput =  pass->GetOutput();
			for(auto& buffer : bufferOutput->buffers)
			{
				TTextureInfo newTex;
				newTex.id = buffer.id;
				newTex.offset = (int)pipelineData.buffers.size();
				newTex.name = buffer.name;
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
		TPipelineDescriptor pipelineDesc(*bento::common_allocator());
		bool res = ResourceManager::Instance().request_asset<TPipelineDescriptor>(_scene->pipelineName.c_str(), pipelineDesc);
		if (!res) return nullptr;

		for(auto& pass : pipelineDesc.passes)
		{
			// Fetching the pointers
			if(pass.tag == TPassTag::GEOMETRY)
			{
				const TPipelineCanvas& canvasDesc = pass.canvas;
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
						canvas = new TEffectCanvas(_width, _height, canvasDesc.output.c_str());
					}
					break;
					case TCanvasTag::GBUFFER:
					{
						canvas = new TGBufferCanvas(_width, _height);
					}
					break;
					default:
						assert_fail_msg("Unexisting canvas type");
					break;
				}

				TGeometryPass* geometryPass = new TGeometryPass(canvas, _scene);
				geometryPass->SetCamera(camera);
				pipeline->passes.push_back(geometryPass);

			}
			else if (pass.tag == TPassTag::VFX)
			{
				const TPipelineCanvas& canvasDesc = pass.canvas;
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
						canvas = new TEffectCanvas(_width, _height, canvasDesc.output.c_str());
					}
					break;
					case TCanvasTag::GBUFFER:
					{
						canvas = new TGBufferCanvas(_width, _height);
					}
					break;
					default:
						assert_fail_msg("Unexisting canvas type");
					break;
				}

				const TPipelineVFX& vfxDescriptor = pass.vfx;
				TVFX* vfx = nullptr;
				switch(vfxDescriptor.tag)
				{
					case TVFXTag::SIMPLEFX:
					{
						TSimpleFX* sfx = new TSimpleFX(vfxDescriptor.shader_pipeline);
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
						if(_scene->skybox != UINT32_MAX)
						{
							TSkyboxFX* skyboxFX = new TSkyboxFX(vfxDescriptor.shader_pipeline);
							skyboxFX->SetSkybox(_scene->skybox);
							skyboxFX->SetCamera(camera);
							vfx = skyboxFX;
						}
					}
					break;
					default:
						assert_fail_msg("Unexisting fx type");
					break;
				}

				if (vfx != nullptr)
				{
					for (auto& shader_data : vfxDescriptor.data)
					{
						switch (shader_data.type)
						{
						case (uint8_t)TShaderDataType::TEXTURE2D:
						{
							vfx->AddTexture(ResourceManager::Instance().fetch_texture_id(shader_data.data.c_str()), shader_data.slot.c_str());
						}
						break;
						}
					}

					TVFXPass* vfxPass = new TVFXPass(canvas, vfx);
					vfxPass->SetCamera(camera);
					pipeline->passes.push_back(vfxPass);
				}
			}
			else
			{
				assert_fail_msg("Unexisting pass type");
			}
		}
		return pipeline;
	}

}