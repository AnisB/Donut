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

// Libarry includes
#include "base/common.h"
#include "core/common.h"
#include "node.h"

// External includes
#include <algorithm>

namespace Donut
{
	// Cst
	TNode::TNode(TAllocator& _alloc)
	: m_transform()
	, m_sons(_alloc)
	{
		// Make sure the root is centered at origin
		matrix4(m_transform, MatrixInit::Identity);
	}

	TNode::~TNode()
	{
		// Delete all the children
		foreach_macro(child, m_sons)
		{
			delete *child;
		}
	}

	// Attach a child
	void TNode::AttachChild(TNode* _node)
	{
		// Quick check
		ASSERT_POINTER_NOT_NULL_NO_RELEASE(_node);

		// Append it to the son list
		m_sons.push_back(_node);
	}

	// Parse this node and its subnodes
	void TNode::Evaluate(TCollector& _requestCollector, const Matrix4& _parentTransform)
	{
		// For each subnode, parse
		foreach_macro(son, m_sons)
		{
			(*son)->Evaluate(_requestCollector, _parentTransform * m_transform);
		}
	}
}