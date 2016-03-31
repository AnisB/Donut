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

	TPipeline* GenerateGraphicPipeline(TScene* _scene, int _width, int _height, TPipelineConfig::Type _pipelineTAGS)
	{
		GRAPHICS_INFO(_width<<" " <<_height);
		// Creating the pipeline
		TPipeline* pipeline = new TPipeline();
		// Fetching its internal data
		pipeline->pipelineData.width = _width;
		pipeline->pipelineData.height = _height;
		Camera* camera =  pipeline->camera;
		TBufferOutput& buffers =  pipeline->pipelineData;
		// If nothing specified, lets just render the first color buffer
		if(_pipelineTAGS == TPipelineConfig::MINIMAL)
		{
			// One pass to rule them all
			TCanvas* canvas = new TEmptyCanvas(_width, _height);
			TGeometryPass* geometryPass = new TGeometryPass(canvas, _scene->root);
			geometryPass->SetCamera(camera);
			pipeline->passes.push_back(geometryPass);
		}
		else if(_pipelineTAGS == TPipelineConfig::REALIST)
		{

			// The first GBuffer Pass
			{
				TCanvas* canvas = new TGBufferCanvas(_width, _height);
				TGeometryPass* geometryPass = new TGeometryPass(canvas, _scene->root);
				geometryPass->SetCamera(camera);
				pipeline->passes.push_back(geometryPass);
			}

			// Deffered Shading
			if(!_scene->lights.empty())
			{
				TCanvas* canvas = new TEffectCanvas(_width, _height, "deffered");
				TDefferedFX* deffered = new TDefferedFX();
				deffered->SetLights(_scene->lights);
				TVFXPass* vfxPass = new TVFXPass(canvas, deffered);
				vfxPass->SetCamera(camera);
				pipeline->passes.push_back(vfxPass);
			}
			
			// Screen space ambien occlusion
			{
				TCanvas* canvas = new TEffectCanvas(_width, _height, "ssao_prefiltered");
				TSimpleFX* afterFX = new TSimpleFX("common/shaders/ssfx/ssao/vertex.glsl", "common/shaders/ssfx/ssao/fragment.glsl");
				afterFX->AddTexture(ResourceManager::Instance().FetchTexture("common/textures/random.jpg"), "random");
				TVFXPass* vfxPass = new TVFXPass(canvas, afterFX);
				vfxPass->SetCamera(camera);
				pipeline->passes.push_back(vfxPass);
			}
			// Filtering it
			{
				TCanvas* canvas = new TEffectCanvas(_width, _height, "ssao_filtered");
				TSimpleFX* afterFX = new TSimpleFX("common/shaders/ssfx/blur/vertex.glsl", "common/shaders/ssfx/blur/fragment.glsl");
				TVFXPass* vfxPass = new TVFXPass(canvas, afterFX);
				vfxPass->SetCamera(camera);
				pipeline->passes.push_back(vfxPass);
			}
			
			// If an envmap has been declared
			if(_scene->sh)
			{
				TCanvas* canvas = new TEffectCanvas(_width, _height, "envmap");
				TEnvironmentFX* afterFX = new TEnvironmentFX();
				afterFX->SetSH(_scene->sh);
				TVFXPass* vfxPass = new TVFXPass(canvas, afterFX);
				vfxPass->SetCamera(camera);
				pipeline->passes.push_back(vfxPass);
			}

			// The compositing pass
			{
				TCanvas* canvas = new TEffectCanvas(_width, _height, "final");
				TSimpleFX* afterFX = new TSimpleFX("common/shaders/ssfx/cmp/vertex.glsl", "common/shaders/ssfx/cmp/fragment.glsl");
				TVFXPass* vfxPass = new TVFXPass(canvas, afterFX);
				vfxPass->SetCamera(camera);
				pipeline->passes.push_back(vfxPass);
			}

			// The after effect DOF pass
			{
				TCanvas* canvas = new TEmptyCanvas(_width, _height);
				TSimpleFX* afterFX = new TSimpleFX("common/shaders/ssfx/dof/vertex.glsl","common/shaders/ssfx/cmp/fragment.glsl");
				TVFXPass* vfxPass = new TVFXPass(canvas, afterFX);
				vfxPass->SetCamera(camera);
				pipeline->passes.push_back(vfxPass);
			}
			
		}
		else
		{
			ASSERT_NOT_IMPLEMENTED();
		}
		return pipeline;
	}

}