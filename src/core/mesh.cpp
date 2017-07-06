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
#include "Mesh.h"
#include "resource/resourcemanager.h"
#include "resource/sugarloader.h"
#include "MultiThread/Defines.h"

// External includes
#include <string.h>


namespace donut
{
	TMesh::TMesh(TOPPING_GUID _toppingGUID, GEOMETRY_GUID _geometry)
 	: TDrawable()
	, m_topping(_toppingGUID)
	, m_geometry(_geometry)
 	{
 	}

 	TMesh::~TMesh()
 	{

 	}
	
	void TMesh::Evaluate(TCollector& _request, const Matrix4& _tm)
	{
		// Build our new render request
		TRenderRequest newRequest;
		newRequest.geometry = m_geometry;
		newRequest.topping = m_topping;
		newRequest.transform = _tm;

		// Appent it
		_request.Append(newRequest);
	}
 }