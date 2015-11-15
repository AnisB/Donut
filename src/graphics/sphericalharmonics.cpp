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
#include "sphericalharmonics.h"
#include "graphics/shadermanager.h"
#include "graphics/common.h"

namespace Donut
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

	void TSphericalHarmonics::InjectData(const TShader& _shader)
	{
		ShaderManager::Instance().InjectV<float>(_shader, &m_red[0], m_degree, "redCoeff");
		ShaderManager::Instance().InjectV<float>(_shader, &m_green[0], m_degree, "greenCoeff");
		ShaderManager::Instance().InjectV<float>(_shader, &m_blue[0], m_degree, "blueCoeff");
	}
}