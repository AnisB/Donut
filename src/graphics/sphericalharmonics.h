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


#ifndef DONUT_ENV_MAP_SH
#define DONUT_ENV_MAP_SH

// STL includes
#include <vector>

namespace donut
{
	// Foward declarations
	struct TShader;
	// Class
	class TSphericalHarmonics
	{
	public:
		TSphericalHarmonics();
		~TSphericalHarmonics();
		void SetCoeffs(const std::vector<float>& _redCoeffs, 
						const std::vector<float>& _greenCoeffs,
						const std::vector<float>& _blueCoeffs);

		void InjectData(const TShader& _shader);
	protected:
		std::vector<float> m_red;
		std::vector<float> m_green;
		std::vector<float> m_blue;
		int m_degree;
	};
}
#endif // DONUT_ENV_MAP_SH
