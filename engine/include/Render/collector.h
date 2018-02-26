#ifndef GRAPHICS_COLLECTOR_H
#define GRAPHICS_COLLECTOR_H

// Library includes
#include "render_request.h"

// External includes
#include <vector>

namespace donut
{
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
		inline std::vector<TRenderRequest>& Requests() {return m_requests;}
		
    protected:
        std::vector<TRenderRequest> m_requests;
	};
}

#endif // GRAPHICS_COLLECTOR_H