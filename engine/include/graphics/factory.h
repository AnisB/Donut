#pragma once

// Library includes
#include "core/mesh.h"

namespace donut
{
	// Foward declaration
	class TSugarInstance;

	GEOMETRY_GUID CreateFullScreenQuad();

	// Drawable factory
	TMesh* CreateSkyboxDrawable(CUBEMAP_GUID cubemap);
	
		// Default meshes
	TMesh* CreateCube(double _length, std::string _materialName = "DEFAULT");
	TMesh* CreateSphere(double _radius, std::string _materialName = "DEFAULT");
	TMesh* CreatePlane(double _with, double _length, std::string _materialName = "DEFAULT");
		// Create a sugar instance
	TSugarInstance* CreateSugarInstance(const char* sugar_name);
}
