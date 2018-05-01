#pragma once

// Internal includes
#include <graphics/drawable.h>

// Bento includes
#include <bento_memory/common.h>
#include <bento_math/matrix4.h>
#include <bento_collection/vector.h>

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

		// Append a drawable to the list of drawables
		virtual void AppendDrawable(TDrawable* _drawables);

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
		bento::Vector<TDrawable*> m_drawables;
		bento::Matrix4 m_transform;
	};
}