// Library include
#include "crumble_remover.h"
#include "resource/resourcemanager.h"
#include "butter/matrix4.h"
#include "butter/vector4.h"

namespace Donut
{
	// Cst
	TCrumbleRemover::TCrumbleRemover()
	{

	}

	// Dst
	TCrumbleRemover::~TCrumbleRemover()
	{

	}

	// Process the render requests
	void TCrumbleRemover::Process(std::vector<TRenderRequest>& _requests, std::vector<TBox3>& _vsBoxes,const Matrix4& _view, const TFrustum& _frusutm)
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

			// Compute the camera space bounding box
			const TBox3& camera_space_bb = transform(geom->os_bb, _view * currentRequest.transform);

			// Is it outside the frustum
			if (_frusutm.MaxScreenPercentage(camera_space_bb) < 0.01f)
			{
				m_discardArray[req] = true;
			}
		}

		// Remove all the non-visible requests
		int finalNbRequests = nbRequests;
		int reqIterator = nbRequests - 1;

		// Put them at the end
		while (reqIterator >= 0)
		{
			if (m_discardArray[reqIterator])
			{
				TRenderRequest tmpReq = _requests[finalNbRequests - 1];
				_requests[finalNbRequests - 1] = _requests[reqIterator];
				_requests[reqIterator] = tmpReq;
				finalNbRequests--;
			}
			reqIterator--;
		}

		// Discard them
		_requests.erase(_requests.begin() + finalNbRequests, _requests.end());
	}
}