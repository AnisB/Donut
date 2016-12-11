// Library include
#include "dispatcher.h"
#include "frustum_culler.h"
#include "crumble_remover.h"
#include "resource/resourcemanager.h"

namespace Donut
{
	TDispatcher::TDispatcher()
	{
		// Nothing to do here
		m_processors.push_back(new TFrustumCuller());
		m_processors.push_back(new TCrumbleRemover());
	}

	void TDispatcher::ProcessRequests(std::vector<TRenderRequest>& _requests, const Matrix4& _view, const TFrustum& _frusutm)
	{
		// Update the dispatcher internal data
		UpdateData(_requests, _view);
		
		// Fetch the requests
		for(auto processor = m_processors.begin(); processor != m_processors.end(); ++processor)
		{
			(*processor)->Process(_requests, m_vs_bb, _view, _frusutm);
		}
	}
	
	TDispatcher::~TDispatcher()
	{
		for(auto processor = m_processors.begin(); processor != m_processors.end(); ++processor)
		{
			delete *processor;
		}
	}

	void TDispatcher::UpdateData(std::vector<TRenderRequest>& _requests, const Matrix4& _view)
	{
		// Allocate any additional space for requests
		size_t nbRequests = _requests.size();
		m_vs_bb.resize(nbRequests);

		// Iterate over the requests
		for (size_t req = 0; req < nbRequests; ++req)
		{
			// Fetch the request to process
			TRenderRequest& currentRequest = _requests[req];

			// Fetch the geometry to process
			TGeometry* geom = ResourceManager::Instance().RequestRuntimeGeometry(currentRequest.geometry);

			// Get the target box
			TBox3& box = m_vs_bb[req];
			box.Reset();

			// Compute the camera space bounding box
			box = transform(geom->os_bb, _view * currentRequest.transform);
		}
	}
}