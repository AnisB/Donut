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

	void TSphericalHarmonics::SetCoeffs(const std::vector<float>& _redCoeffs, const std::vector<float>& _greenCoeffs, const std::vector<float>& _blueCoeffs)
	{
		m_degree = _redCoeffs.size();
		m_red = _redCoeffs;
		m_blue = _blueCoeffs;
		m_green = _greenCoeffs;
	}

	void TSphericalHarmonics::InjectData(ShaderPipelineObject _shader)
	{
		ShaderManager::Instance().InjectV<float>(_shader, &m_red[0], m_degree, "redCoeff");
		ShaderManager::Instance().InjectV<float>(_shader, &m_green[0], m_degree, "greenCoeff");
		ShaderManager::Instance().InjectV<float>(_shader, &m_blue[0], m_degree, "blueCoeff");
	}
}