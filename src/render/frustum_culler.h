#ifndef FRUSTUM_CULLER_H
#define FRUSTUM_CULLER_H

// Library includes
#include "render_request.h"
#include "core/box3.h"

namespace Donut
{
	// This class is able to process frustrum culling for a given set of render requests
	class TFrustumCuller
	{
	public:
		// Cst and Dst
		TFrustumCuller();
		~TFrustumCuller();

		// This function modifies the set of render requests based on the fact that the concerned geometries as inside or outside
		// the view frsutum that has been specified as an input
		void Process(std::vector<TRenderRequest>& _requests, const Matrix4& _view);

	protected:
		std::vector<char> m_discardArray;
		std::vector<TBox3> m_wsBoxes;
	};
}
#endif // FRUSTUM_CULLER_H