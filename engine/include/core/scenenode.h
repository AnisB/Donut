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