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

#include "geometrypass.h"
#include "graphics/common.h"
#include "base/Common.h"
#include "Base/Macro.h"
#include "resource/resourcemanager.h"

 namespace Donut
 {

 	//CLASS IMPLEMENTATION
	TGeometryPass::TGeometryPass()
	: m_canvas(nullptr)
	, m_root(nullptr)
	, m_reference()
	{
		FCamera = new Camera();
		SetIdentity(m_reference);
	}
	TGeometryPass::~TGeometryPass()
	{
		delete FCamera;
	}

	void TGeometryPass::Set(TCanvas* _canvas, TNode* _root)
	{
		m_canvas = _canvas;
		m_root = _root;
	}
	
	void TGeometryPass::Init()
	{
		m_canvas->Init();
	}

	void TGeometryPass::Draw(const TBufferOutput& _previousData)
	{
		// Building common uniforms
		std::map<std::string, TUniformHandler> values;
		FCamera->AppendUniforms(values);
		TUniformHandler model;
		model.SetValue(TShaderData::MAT4, "model", m_reference);
		values["model"] = model;
		// Drawing me
		m_root->Draw(values, _previousData);
	}

	void TGeometryPass::Bind()
	{
		m_canvas->Enable();
	}
	const TBufferOutput* TGeometryPass::GetOutput()
	{
		return &(m_canvas->Result());
	}

	void TGeometryPass::Unbind()
	{
		m_canvas->Disable();
	}

	// END CLASS IMPLEMENTATION
 }
