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
#include "graphics/uniformhandler.h"
#include "graphics/canvas.h"
#include "camera.h"

// STL includes
#include <vector>

namespace Donut
{
    // Foward declare
    class TCollector;
    
    // Basic Node class of the engine
	class TNode
	{
	public:
		// Consrtuctor
		TNode();
		//Destructor
		virtual ~TNode();

		// Adds a child to the tree
		void AttachChild(TNode* _childNode);
		// WARNING: You should preferably not call this, maybe disable your node?
		bool RemoveChild(TNode* _childNode);

		// Utility functions
		void SetTransformationMatrix(const Matrix4& _tm) { m_transform =_tm;}

		// Access the son set
		const std::vector<TNode*>& ChildList() {return m_sons;}
		
		// Evaluate this node and its subnodes
		virtual void Evaluate(TCollector& _requestCollector, const Matrix4& _parentTransform);

	protected:
		// Node data
		TNode* m_parent;
		std::vector<TNode*> m_sons;
		Matrix4 m_transform;
	};
}
#endif