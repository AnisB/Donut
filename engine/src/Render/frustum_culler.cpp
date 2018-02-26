// Library include
#include "render/frustum_culler.h"
#include "resource/resourcemanager.h"
#include "butter/matrix4.h"
#include "butter/vector4.h"

namespace donut
{
	// Cst
	TFrustumCuller::TFrustumCuller()
	{

	}

	// Dst
	TFrustumCuller::~TFrustumCuller()
	{

	}

	// Process the render requests
	void TFrustumCuller::Process(std::vector<TRenderRequest>& _requests, std::vector<TBox3>& _vsBoxes, const Matrix4&, const TFrustum& _frusutm)
	{
		// Fetch the amount of remaining requests to process
		size_t nbRequests = _requests.size();

		// Quick exit if nothing is left to be done
		if (nbRequests == 0) return;

		// Make sure that we have all the memory we need
		m_discardArray.resize(nbRequests);

		// Intialize the arrays
		memset(&m_discardArray[0], 0, nbRequests);

		// Iterate over the requests
		for (size_t req = 0; req < nbRequests; ++req)
		{
			// Is it outside the frustum
			if (_frusutm.BoxOutside(_vsBoxes[req]))
			{
				m_discardArray[req] = true;
			}
		}

		// Remove all the non-visible requests
		int finalNbRequests = (int)nbRequests;
		int reqIterator = (int)nbRequests - 1;

		// Put them at the end
		while (reqIterator >= 0)
		{
			if (m_discardArray[reqIterator])
			{
				// Swap the render request
				TRenderRequest tmpReq = _requests[finalNbRequests - 1];
				_requests[finalNbRequests - 1] = _requests[reqIterator];
				_requests[reqIterator] = tmpReq;

				// Swap the bounding box
				TBox3 tmpBox = _vsBoxes[finalNbRequests - 1];
				_vsBoxes[finalNbRequests - 1] = _vsBoxes[reqIterator];
				_vsBoxes[reqIterator] = tmpBox;

				finalNbRequests--;
			}
			reqIterator--;
		}

		// Discard request and boxes
		_requests.erase(_requests.begin() + finalNbRequests, _requests.end());
		_vsBoxes.erase(_vsBoxes.begin() + finalNbRequests, _vsBoxes.end());
	}
}