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
#include "emptycanvas.h"
#include "base/macro.h"
#include "graphics/gbuffercanvas.h"
#include "resource/resourcemanager.h"
#include "graphics/vfxpass.h"
#include "graphics/simplefx.h"
#include "graphics/defferedfx.h"
#include "graphics/emptycanvas.h"
#include "graphics/simplecanvas.h"
#include "graphics/geometrypass.h"

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
	TPipeline* GenerateGraphicPipeline(TNode* _rootNode, std::vector<TLight*> _lights, int _width, int _height, int _graphicPipelineTAGS)
	{
		TPipeline* pipeline = new TPipeline();
		Camera* camera =  pipeline->camera;
		if(_graphicPipelineTAGS == TPipelineTAG::SIMPLE)
		{
			// One pass to rule them all
			TCanvas* canvas = new TEmptyCanvas(_width, _height);
			TGeometryPass* geometryPass = new TGeometryPass(canvas, _rootNode);
			geometryPass->SetCamera(camera);
			pipeline->passes.push_back(geometryPass);
		}
		else if(_graphicPipelineTAGS == TPipelineTAG::DEFFERED)
		{
			// The first GBuffer Pass
			{
				TCanvas* canvas = new TGBufferCanvas(_width, _height);
				TGeometryPass* geometryPass = new TGeometryPass(canvas, _rootNode);
				geometryPass->SetCamera(camera);
				pipeline->passes.push_back(geometryPass);
			}

			// The second deffered pass
			{
				TCanvas* canvas = new TEmptyCanvas(_width, _height);
				TDefferedFX* deffered = new TDefferedFX();
				deffered->SetLights(_lights);
				TVFXPass* vfxPass = new TVFXPass(canvas, deffered);
				vfxPass->SetCamera(camera);
				pipeline->passes.push_back(vfxPass);
			}
		}
		else if(_graphicPipelineTAGS == TPipelineTAG::DOF)
		{
			// The first GBuffer Pass
			{
				TCanvas* canvas = new TSimpleCanvas(_width, _height);
				TGeometryPass* geometryPass = new TGeometryPass(canvas, _rootNode);
				geometryPass->SetCamera(camera);
				pipeline->passes.push_back(geometryPass);
			}

			// The second deffered pass
			{
				TCanvas* canvas = new TEmptyCanvas(_width, _height);
				TSimpleFX* afterFX = new TSimpleFX("data/shaders/canvas/dofV.glsl","data/shaders/canvas/dofF.glsl");
				TVFXPass* vfxPass = new TVFXPass(canvas, afterFX);
				vfxPass->SetCamera(camera);
				pipeline->passes.push_back(vfxPass);
			}
		}
		else if(_graphicPipelineTAGS == TPipelineTAG::SSAO)
		{
			// The first GBuffer Pass
			{
				TCanvas* canvas = new TSimpleCanvas(_width, _height);
				TGeometryPass* geometryPass = new TGeometryPass(canvas, _rootNode);
				geometryPass->SetCamera(camera);
				pipeline->passes.push_back(geometryPass);
			}

			// The second deffered pass
			{
				TCanvas* canvas = new TEmptyCanvas(_width, _height);
				TSimpleFX* afterFX = new TSimpleFX("shaders/canvas/ssaoV.glsl", "shaders/canvas/ssaoF.glsl");
				afterFX->AddTexture(ResourceManager::Instance().FetchTexture("data/textures/random.jpg"), "random");
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