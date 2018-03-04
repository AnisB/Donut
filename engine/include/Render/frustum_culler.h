#ifndef FRUSTUM_CULLER_H
#define FRUSTUM_CULLER_H

// Library includes
#include "processor.h"
#include "render_request.h"
#include "core/frustum.h"
#include "core/box3.h"

namespace donut
{
	// This class is able to process frustrum culling for a given set of render requests
	class TFrustumCuller : public TProcessor
	{
	public:
		// Cst and Dst
		TFrustumCuller();
		~TFrustumCuller();

		// This function modifies the set of render requests based on the fact that the concerned geometries as inside or outside
		// the view frsutum that has been specified as an input
		void Process(std::vector<TRenderRequest>& _requests, std::vector<TBox3>& _vsBoxes, const bento::Matrix4& _view, const TFrustum& _frusutm);

	protected:
		std::vector<char> m_discardArray;
	};
}
#endif // FRUSTUM_CULLER_H