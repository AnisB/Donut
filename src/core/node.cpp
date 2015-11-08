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
#include "node.h"
#include "base/common.h"
#include "core/common.h"
// STL includes
#include <algorithm>

namespace Donut
{
	TNode::TNode()
	: FModel()
	{
		matrix4(FModel, MatrixInit::Identity);
	}

	TNode::~TNode()
	{
		foreach_macro(child, FSons)
		{
			delete *child;
		}
	}
	void TNode::AttachChild(TNode* _node)
	{
		FSons.push_back(_node);
	}
	bool TNode::RemoveChild(TNode* _node)
	{
		CORE_DEBUG("Maybe you should not call this function, preferably disabled");
		auto nodeIT = std::find(FSons.begin(), FSons.end(), _node);
		ASSERT(nodeIT != FSons.end());
		if(nodeIT != FSons.end())
		{
			FSons.erase(nodeIT);
			return true;
		}
		else
		{
			return false;
		}
	}

	void TNode::Yaw(float parAngle)
	{
		FModel = FModel*RotateYAxis(parAngle);

	}
	void TNode::Roll(float parAngle)
	{
		FModel = FModel*RotateZAxis(parAngle);
	}
	void TNode::Pitch(float parAngle)
	{
		FModel = FModel*RotateXAxis(parAngle);
	}	
	void TNode::Draw(const Matrix4& _modelMatrix, const Matrix4& _viewProjectionMatrix, const std::vector<TUniformHandler>& _handler)
	{
		foreach_macro(son,FSons)
		{
			(*son)->Draw(_modelMatrix*FModel, _viewProjectionMatrix, _handler);
		}
	}
	void TNode::Translate(const Vector3& parVector)
	{
 		FModel = FModel*Translate_M4(parVector);
	}

	const std::vector<TNode*>& TNode::GetChildList()
	{
		return FSons;	
	}
}