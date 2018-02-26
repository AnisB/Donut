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

#include "graphics/vfxpass.h"
#include "graphics/common.h"
#include "resource/resourcemanager.h"

 namespace donut
 {
 	//CLASS IMPLEMENTATION
	TVFXPass::TVFXPass(TCanvas* _canvas, TVFX* _vfx)
	: m_canvas(_canvas)
	, m_vfx(_vfx)
	{
	}

	TVFXPass::~TVFXPass()
	{
	}

	void TVFXPass::Init()
	{
		m_canvas->Init();
		m_vfx->Init();
	}

	void TVFXPass::Draw(const TBufferOutput& _previousData)
	{
		// Building common uniforms
		m_camera->AppendUniforms(m_values);
		m_vfx->Draw(m_values, _previousData);
	}

	void TVFXPass::Bind()
	{
		m_canvas->Enable();
	}

	const TBufferOutput* TVFXPass::GetOutput()
	{
		return &(m_canvas->Result());
	}

	void TVFXPass::Unbind()
	{
		m_canvas->Disable();
	}

	// END CLASS IMPLEMENTATION
 }
