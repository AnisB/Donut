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

// Std includes
#include "bento_collection/vector.h"

// Bento includes
#include <bento_memory/common.h>
#include <bento_math/matrix4.h>

// STL includes
#include <vector>

namespace donut
{
    // Foward declare
    class TCollector;
    
    // Basic Node class of the engine
	class TNode
	{
	public:
		ALLOCATOR_BASED;
		// Consrtuctor
		TNode(bento::IAllocator& _alloc);
		//Destructor
		virtual ~TNode();

		// Adds a child to the tree
		void AttachChild(TNode* _childNode);
		// WARNING: You should preferably not call this, maybe disable your node?
		bool RemoveChild(TNode* _childNode);

		// Utility functions
		void SetTransformationMatrix(const bento::Matrix4& _tm) { m_transform =_tm;}

		// Access the son set
		const bento::Vector<TNode*>& ChildList() {return m_sons;}
		
		// Evaluate this node and its subnodes
		virtual void Evaluate(TCollector& _requestCollector, const bento::Matrix4& _parentTransform);

	protected:
		// Node data
		TNode* m_parent;
		bento::Vector<TNode*> m_sons;
		bento::Matrix4 m_transform;
	};
}