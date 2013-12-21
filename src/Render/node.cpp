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

namespace Donut
{
	TNode::TNode()
	: FModel(MatrixInit::Identity)
	{

	}

	TNode::~TNode()
	{
		
	}
	void TNode::AddChild(TNode* parNode)
	{
		FSons.push_back(parNode);
	}
	bool TNode::RemoveChild(TNode* parNode)
	{
		size_t initial = FSons.size();
		FSons.remove(parNode);
		return (initial!=FSons.size());
	}

	void TNode::Yaw(float parAngle)
	{
		FModel = Matrix4::rotateYAxis(parAngle)*FModel;

	}
	void TNode::Roll(float parAngle)
	{
		FModel = Matrix4::rotateZAxis(parAngle)*FModel;
	}
	void TNode::Pitch(float parAngle)
	{
		FModel = Matrix4::rotateXAxis(parAngle)*FModel;
	}	
	void TNode::Draw(const Matrix4& parModelMatrix, Camera* parCamera)
	{
		foreach(son,FSons)
		{
			(*son)->Draw(parModelMatrix*FModel,parCamera);
		}
	}

	const std::list<TNode*>& TNode::GetChildList()
	{
		return FSons;	
	}
}