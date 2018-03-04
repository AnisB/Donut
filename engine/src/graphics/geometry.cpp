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
#include "graphics/geometry.h"

namespace donut
{
    void TGeometry::Draw(bool _isTess) const
    {
	  	glBindVertexArray (vertexArray);
	  	if(_isTess)
	  	{
	  		glDrawElements(GL_PATCHES, nbVertices, GL_UNSIGNED_INT, 0);
	  	}
	  	else
	  	{
	  		glDrawElements(GL_TRIANGLES, nbVertices, GL_UNSIGNED_INT, 0);
	  	}
	  	glBindVertexArray (0);
    }
}