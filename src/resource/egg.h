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

#ifndef EGG_RESOURCE_DONUT
#define EGG_RESOURCE_DONUT

// STL includes
#include <fstream>

namespace Donut
{
	struct TEgg
	{
		TEgg()
		: vertsNormalsUVs(nullptr)
        , faces(nullptr)
		{
		}

		~TEgg()
		{
			if(vertsNormalsUVs != nullptr)
			{
				delete [] vertsNormalsUVs;
			}
			if(faces != nullptr)
			{
				delete [] faces;
			}
		}

		// Mesh data
	    int nbFaces;
	    int nbVertices;
	    float* vertsNormalsUVs;
	    unsigned int* faces;
	};

	std::ostream& operator<<(std::ostream& _os, const TEgg& _eggInstance);
	std::istream& operator>>(std::istream& _is, TEgg& _eggInstance);
}


#endif // EGG_RESOURCE_DONUT
 