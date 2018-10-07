// Library include
#include "render/dispatcher.h"
#include "render/frustum_culler.h"
#include "render/crumble_remover.h"
#include "resource/resource_manager.h"

// Bento includes
#include "bento_math/matrix4.h"

namespace donut
{
	TDispatcher::TDispatcher(const GPUBackendAPI* backendAPI)
	: _gpuBackend(backendAPI)
	{
		// Nothing to do here
		//m_processors.push_back(new TFrustumCuller());
		//m_processors.push_back(new TCrumbleRemover());
	}

	void TDispatcher::ProcessRequests(std::vector<TRenderRequest>& _requests, const bento::Matrix4& _view, const TFrustum& _frusutm)
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

	void TDispatcher::UpdateData(std::vector<TRenderRequest>& _requests, const bento::Matrix4& _view)
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
			GeometryObject geom = ResourceManager::Instance().request_runtime_geometry(currentRequest.geometry);
			const TMaterial& mat = ResourceManager::Instance().request_runtime_material(currentRequest.material);

			// Propagate the flags that have been raised by the material
			currentRequest.render_flags = currentRequest.render_flags | mat.flags;

			// Get the target box
			TBox3& box = m_vs_bb[req];
			_gpuBackend->geometry_api.bbox(geom, box);

			// Compute the camera space bounding box
			box = box::transform(box, _view * currentRequest.transform);
		}
	}
}