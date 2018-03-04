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

#pragma once

// donut includes
#include "graphics/drawable.h"
#include "node.h"

// Bento includes
#include <bento_collection/vector.h>
#include <bento_memory/common.h>

// External includes
#include <vector>

namespace donut
{
	// Foward declaration
	class TCollector;

	// This class encapsulates the data for a graph scene node
	class TSceneNode : public TNode
	{
	public:
		ALLOCATOR_BASED;
		// Consrtuctor
		TSceneNode(bento::IAllocator& _alloc);

		// Destructor
		~TSceneNode();

		// Append a drawable to the list of drawables
		virtual void AppendDrawable(TDrawable* _drawables);

		// Evaluate this node and its subnodes
		virtual void Evaluate(TCollector& _requestCollector, const bento::Matrix4& _parentTransform);

	protected:
		bento::Vector<TDrawable*> m_drawables;
	};
}