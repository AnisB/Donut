#ifndef GRAPHICS_COLLECTOR_H
#define GRAPHICS_COLLECTOR_H

// Library includes
#include "butter/types.h"
#include "graphics/uniformhandler.h"

// External includes
#include <vector>
#include <map>

namespace Donut
{
    // Foward declare
    class TMaterial;
    class TGeometry;
    
	// This structure encapsulates everything that is required to draw a geometry with a material
	struct TRenderRequest
	{
		// Instance data
		const TMaterial* material;
		const TGeometry* geometry;

		// Mesh transform
		Matrix4 transform;
	};
	// Processed a render request
	void ProcessRenderRequest(const TRenderRequest& _request, std::map<std::string, TUniformHandler>& _uniforms);

	class TCollector
	{
	public:
		// Cst & Dst
		TCollector();
		~TCollector();

		// Access functions
			// Clears the render calls
		void Clear();
		void Append(const TRenderRequest& _request) {m_requests.push_back(_request);}
		const std::vector<TRenderRequest>& Requests() {return m_requests;}
		
    protected:
        std::vector<TRenderRequest> m_requests;
	};
}

#endif // GRAPHICS_COLLECTOR_H