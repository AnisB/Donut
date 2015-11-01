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

#ifndef DONUT_NODE
#define DONUT_NODE


// Std includes
#include "butter/matrix4.h"
#include "camera.h"

// STL includes
#include <vector>

namespace Donut
{
	class TNode
	{
	public:
		// Consrtuctor
		TNode();
		//Destructor
		~TNode();
		// Adds a child to the tree
		void AddChild(TNode* parNode);
		bool RemoveChild(TNode* parNode);

		void Yaw(float parAngle);
		void Roll(float parAngle);
		void Pitch(float parAngle);

		void Translate(const Vector3& parVector);
		const std::vector<TNode*>& GetChildList();
		virtual void Draw(const Matrix4& _modelMatrix, const Matrix4& _viewProjectionMatrix);

	protected:
		std::vector<TNode*> FSons;
		TNode* FParent;
		Matrix4 FModel;
	};
}
#endif