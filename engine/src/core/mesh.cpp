// Library includes
#include "core/Mesh.h"
#include "resource/resource_manager.h"

// External includes
#include <string.h>

namespace donut
{
	TMesh::TMesh(MATERIAL_GUID material_guid, GEOMETRY_GUID _geometry)
 	: TDrawable()
	, m_material(material_guid)
	, m_geometry(_geometry)
 	{
 	}

 	TMesh::~TMesh()
 	{

 	}
	
	void TMesh::Evaluate(TCollector& _request, const bento::Matrix4& _tm)
	{
		// Build our new render request
		TRenderRequest newRequest;
		newRequest.geometry = m_geometry;
		newRequest.material = m_material;
		newRequest.transform = _tm;
		// Appent it
		_request.Append(newRequest);
	}
 }