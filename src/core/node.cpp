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
 #include "Node.h"
 #include <Base/Common.h>
 #include "Base/Macro.h"

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
	void TNode::AddChild(TNode* parNode)
	{
		FSons.push_back(parNode);
	}
	bool TNode::RemoveChild(TNode* parNode)
	{
		ASSERT_NOT_IMPLEMENTED();
		return false;
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
	void TNode::Draw(const Matrix4& _modelMatrix, const Matrix4& _viewProjectionMatrix)
	{
		foreach_macro(son,FSons)
		{
			(*son)->Draw(_modelMatrix*FModel, _viewProjectionMatrix);
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