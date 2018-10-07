#include "graphics/vfxpass.h"
#include "resource/resource_manager.h"

 namespace donut
 {
	TVFXPass::TVFXPass(TCanvas* _canvas, TVFX* _vfx, const char* name, bento::IAllocator& allocator, const GPUBackendAPI* backendAPI)
	: TPass(name, allocator, backendAPI)
	, m_canvas(_canvas)
	, m_vfx(_vfx)
	, m_values()
	{
	}

	TVFXPass::~TVFXPass()
	{
	}

	void TVFXPass::Init()
	{
		m_canvas->init();
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
		m_canvas->enable();
	}

	const TBufferOutput* TVFXPass::GetOutput()
	{
		return &(m_canvas->result());
	}

	void TVFXPass::Unbind()
	{
		m_canvas->disable();
	}
 }
