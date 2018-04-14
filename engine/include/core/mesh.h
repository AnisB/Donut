#pragma once

#include "graphics/drawable.h"
#include "graphics/canvas.h"
#include "graphics/material.h"
#include "resource/texture.h"

// Library includes
#include <map>

 namespace donut
 {
	class TMesh : public TDrawable
	{
	public:
	 	// Creating a mesh
		TMesh(TOPPING_GUID _topping, GEOMETRY_GUID _geometry);
		
		// Dstructor
	 	virtual ~TMesh();

		// Evaluate the mesh
		virtual void Evaluate(TCollector& _collector, const bento::Matrix4& _tm);
		
	protected:
	 	// All the required attributes for drawing a mesh
		TOPPING_GUID m_topping;
		GEOMETRY_GUID m_geometry;
	 };
}