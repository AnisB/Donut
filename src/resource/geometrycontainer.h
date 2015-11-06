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

#ifndef GEOMETRY_CONTAINER_RESOURCE_DONUT
#define GEOMETRY_CONTAINER_RESOURCE_DONUT

// STL includes
#include <fstream>

namespace Donut
{
	struct TGeometryContainer
	{
		TGeometryContainer()
		: faces(nullptr)
		, vertsNormalsUVs(nullptr)
		{
		}

		~TGeometryContainer()
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

	    int nbFaces;
	    int nbVertices;
	    float* vertsNormalsUVs;
	    unsigned int* faces;
	};	
}


#endif // GEOMETRY_CONTAINER_RESOURCE_DONUT
 