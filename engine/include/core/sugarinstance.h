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

#ifndef DONUT_SUGAR_INSTANCE_NODE
#define DONUT_SUGAR_INSTANCE_NODE

// donut includes
#include "node.h"
#include "graphics/drawable.h"

// STL includes
#include <vector>

namespace donut
{
	// Foward declaration
	class TMesh;

	class TSugarInstance : public TDrawable
	{
	public:
		// Consrtuctor
		TSugarInstance();
		//Destructor
		~TSugarInstance();

		// Lethods
		void AddMesh(TMesh* _mesh);
		TMesh* GetMesh(int _meshIndex);

			// Evaluate the sugar instance
		virtual void Evaluate(TCollector& _collector, const Matrix4& _tm);

	protected:
		std::vector<TMesh*> m_meshes;
	};
}
#endif //DONUT_SUGAR_INSTANCE_NODE