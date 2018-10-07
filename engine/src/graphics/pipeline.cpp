// Bento includes
#include <bento_base/security.h>

// Library includes
#include "graphics/pipeline.h"
#include "resource/pipeline_descriptor.h"
// Canvas
#include "graphics/canvas.h"

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

	TPipeline* GenerateGraphicPipeline(TFlour* _scene, int _width, int _height, const donut::GPUBackendAPI* gpuBackend)
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
			// Fetch the canvas descriptor
			const TPipelineCanvas& canvasDesc = pass.canvas;

			// Build the canvas buffer output
			uint32_t numOutputs = canvasDesc.outputs.size();
			TBufferOutput canvasOutput;
			canvasOutput.width = _width;
			canvasOutput.height = _height;
			canvasOutput.depthTest = canvasDesc.depthTest;
			canvasOutput.buffers.resize(numOutputs);
			for (uint32_t outputIdx = 0; outputIdx < numOutputs; ++outputIdx)
			{
				canvasOutput.buffers[outputIdx].name = canvasDesc.outputs[outputIdx].slot.c_str();
				canvasOutput.buffers[outputIdx].type = canvasDesc.outputs[outputIdx].nature;
				canvasOutput.buffers[outputIdx].offset = outputIdx;
			}

			// Create a canvas and fill it based on its type
			TCanvas* canvas = new TCanvas(gpuBackend);
			canvas->setup(canvasOutput);

			// Fetching the pointers
			if(pass.tag == TPassTag::GEOMETRY)
			{
				TGeometryPass* geometryPass = new TGeometryPass(canvas, _scene, pass.name.c_str(), *bento::common_allocator(), gpuBackend);
				geometryPass->SetCamera(camera);
				pipeline->passes.push_back(geometryPass);

			}
			else if (pass.tag == TPassTag::VFX)
			{
				const TPipelineVFX& vfxDescriptor = pass.vfx;
				TVFX* vfx = nullptr;
				switch(vfxDescriptor.tag)
				{
					case TVFXTag::SIMPLEFX:
					{
						TSimpleFX* sfx = new TSimpleFX(vfxDescriptor.shader_pipeline, gpuBackend);
						vfx = sfx;
					}
					break;
					case TVFXTag::ENVIRONEMENT:
					{
						if(_scene->sh)
						{
							TEnvironmentFX* envFX = new TEnvironmentFX(gpuBackend);
							envFX->SetSH(_scene->sh);
							vfx = envFX;
						}
					}
					break;
					case TVFXTag::DEFFERED:
					{
						TDefferedFX* deffered = new TDefferedFX(gpuBackend);
						deffered->SetLights(_scene->lights);
						vfx = deffered;
					}
					break;
					case TVFXTag::SKYBOX:
					{
						if(_scene->skybox != UINT32_MAX)
						{
							TSkyboxFX* skyboxFX = new TSkyboxFX(vfxDescriptor.shader_pipeline, gpuBackend);
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

					TVFXPass* vfxPass = new TVFXPass(canvas, vfx, pass.name.c_str(), *bento::common_allocator(), gpuBackend);
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