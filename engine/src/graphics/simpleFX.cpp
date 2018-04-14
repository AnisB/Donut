// Library includes
#include "graphics/simplefx.h"
#include "graphics/shadermanager.h"
#include "gpu_backend/gl_factory.h"

namespace donut
{
	// Constructor
	TSimpleFX::TSimpleFX(const STRING_TYPE& _vertex, const STRING_TYPE& _fragment)
	: TVFX(TShader(_vertex, _fragment))
	{

	}
	TSimpleFX::TSimpleFX(const TShader& _shader)
	: TVFX(_shader)
	{
	}

	// Destructor
	TSimpleFX::~TSimpleFX()
	{

	}

	// Init
	void TSimpleFX::Init()
	{
		TVFX::Init();
	}

	void TSimpleFX::Draw(std::map<STRING_TYPE, TUniformHandler>& _values, const TBufferOutput& _previousData)
	{
		ShaderManager::Instance().EnableShader(m_material.shader);
		BindBufferOutput(_values, _previousData);
		gl::geometry::draw(m_fsq);
 		ShaderManager::Instance().DisableShader();
	}
}
