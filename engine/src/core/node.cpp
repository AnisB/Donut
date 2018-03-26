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

// Bento includes
#include <bento_base/security.h>

// Libarry includes
#include "core/common.h"
#include "core/node.h"

// External includes
#include <algorithm>

namespace donut
{
	// Cst
	TNode::TNode(bento::IAllocator& _alloc)
	: m_transform()
	, m_sons(_alloc)
	, m_parent(nullptr)
	{
		// Make sure the root is centered at origin
		bento::SetIdentity(m_transform);
	}

	TNode::~TNode()
	{
		// Delete all the children
		for(auto child : m_sons)
		{
			delete child;
		}
	}

	// Attach a child
	void TNode::AttachChild(TNode* _node)
	{
		// Quick check
		assert(_node);

		// Append it to the son list
		m_sons.push_back(_node);
	}

	// Parse this node and its subnodes
	void TNode::Evaluate(TCollector& _requestCollector, const bento::Matrix4& _parentTransform)
	{
		// For each subnode, parse
		for(auto son : m_sons)
		{
			son->Evaluate(_requestCollector, _parentTransform * m_transform);
		}
	}
}