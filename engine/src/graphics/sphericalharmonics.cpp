// Library includes
#include "graphics/sphericalharmonics.h"

namespace donut
{
	TSphericalHarmonics::TSphericalHarmonics()
	{

	}

	TSphericalHarmonics::~TSphericalHarmonics()
	{

	}

	void TSphericalHarmonics::SetCoeffs(const float* _redCoeffs, const float* _greenCoeffs, const float* _blueCoeffs)
	{
		m_red.resize(9);
		m_green.resize(9);
		m_blue.resize(9);
		for (uint32_t coef_idx = 0; coef_idx < 9; ++coef_idx)
		{
			m_red[coef_idx] = _redCoeffs[coef_idx];
			m_green[coef_idx] = _greenCoeffs[coef_idx];
			m_blue[coef_idx] = _blueCoeffs[coef_idx];
		}
	}

	void TSphericalHarmonics::InjectData(ShaderPipelineObject _shader, const GPUBackendAPI* backendAPI)
	{
		backendAPI->shader_api.inject_array(_shader, &m_red[0], 9, "redCoeff");
		backendAPI->shader_api.inject_array(_shader, &m_green[0], 9, "greenCoeff");
		backendAPI->shader_api.inject_array(_shader, &m_blue[0], 9, "blueCoeff");
	}
}