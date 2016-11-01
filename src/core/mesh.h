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


#ifndef DONUT_MESH
#define DONUT_MESH

#include "graphics/drawable.h"
#include "graphics/geometry.h"
#include "graphics/canvas.h"
#include "graphics/material.h"
#include "resource/texture.h"

// Library includes
#include <map>

 namespace Donut
 {
	class TMesh : public TDrawable
	{
	public:
	 	// Creating a mesh
		TMesh(const TMaterial* _material, const TGeometry* _model);
		
		// Dstructor
	 	virtual ~TMesh();

		// Evaluate the mesh
		virtual void Evaluate(TCollector& _collector, const Matrix4& _tm);
		
	protected:
	 	// All the required attributes for drawing a mesh
	 	const TMaterial* m_material;
	 	const TGeometry* m_geometry;
	 };
}
 #endif // DONUT_MESH