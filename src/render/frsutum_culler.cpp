// Library include
#include "frustum_culler.h"
#include "resource/resourcemanager.h"
#include "butter/matrix4.h"

namespace Donut
{
	TFrustumCuller::TFrustumCuller()
	{

	}

	TFrustumCuller::~TFrustumCuller()
	{

	}

	void TFrustumCuller::Process(std::vector<TRenderRequest>& _requests, const Matrix4& _view)
	{
		// Fetch the amount of remaining requests to process
		size_t nbRequests = _requests.size();

		// Quick exit if nothing is left to be done
		if (nbRequests == 0) return;

		// Make sure that we have all the memory we need
		m_discardArray.resize(nbRequests);
		m_wsBoxes.resize(nbRequests);

		// Intialize the arrays
		memset(&m_discardArray[0], 0, nbRequests);

		// Iterate over the requests
		for (size_t req = 0; req < nbRequests; ++req)
		{
			// Fetch the request to process
			TRenderRequest& currentRequest = _requests[req];

			// Fetch the geometry to process
			TGeometry* geom = ResourceManager::Instance().RequestRuntimeGeometry(currentRequest.geometry);

			// Get the target box
			TBox3& box = m_wsBoxes[req];
			box.Reset();

			// Include them in WS
			box.IncludePoint(_view * currentRequest.transform * geom->os_bb.min);
			box.IncludePoint(_view * currentRequest.transform * geom->os_bb.max);
		}

		// Remove all the non-visible requests
		size_t reqIterator = nbRequests - 1;
		size_t lastReqIndx = reqIterator;

		// Put them at the end
		while (reqIterator > 0)
		{
			if (m_discardArray[reqIterator])
			{
				TRenderRequest tmpReq = _requests[lastReqIndx];
				_requests[lastReqIndx] = _requests[reqIterator];
				_requests[reqIterator] = tmpReq;
				lastReqIndx--;
			}
			reqIterator--;
		}

		// Discard them
		_requests.erase(_requests.begin() + lastReqIndx, _requests.end());
	}
}