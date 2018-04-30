// Library includes
#include "graphics/sphericalharmonics.h"
#include "graphics/shadermanager.h"

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

	void TSphericalHarmonics::InjectData(ShaderPipelineObject _shader)
	{
		ShaderManager::Instance().InjectV<float>(_shader, &m_red[0], m_degree, "redCoeff");
		ShaderManager::Instance().InjectV<float>(_shader, &m_green[0], m_degree, "greenCoeff");
		ShaderManager::Instance().InjectV<float>(_shader, &m_blue[0], m_degree, "blueCoeff");
	}
}