#pragma once

// Library includes
#include "processor.h"
#include "gpu_backend/gpu_backend.h"

// Bento includes
#include <bento_math/types.h>

// External includes
#include <vector>

namespace donut
{
	class TDispatcher
	{
	public:
		TDispatcher(const GPUBackendAPI* gpuBackend);
		~TDispatcher();

		void ProcessRequests(std::vector<TRenderRequest>& _requests, const bento::Matrix4& _view, const TFrustum& _frusutm);
	protected:
		void UpdateData(std::vector<TRenderRequest>& _requests, const bento::Matrix4& _view);
	protected:
		const GPUBackendAPI* _gpuBackend;
		std::vector<TProcessor*> m_processors;
		std::vector<TBox3> m_vs_bb;
	};
}