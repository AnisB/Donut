#ifndef FLOUR_LOADER_H
#define FLOUR_LOADER_H

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
#include "recipe/flourdescriptor.h"
#include "base/Singleton.h"
// Extrernal includes
#include <map>

namespace donut 
{
	class TFlourLoader : public Singleton<TFlourLoader>
	{
	public:
		TFlourLoader();
		~TFlourLoader();

		// Init levels
		void Init();
		const TFlourDescriptor& FetchFlour(const STRING_TYPE& _flourFileName);

	protected:
		void LoadFlours();
		
	protected:
		std::map<STRING_TYPE, TFlourDescriptor> m_flours;
	};
}
#endif // FLOUR_LOADER_H