#ifndef REQUEST_DISPATCHER_H
#define REQUEST_DISPATCHER_H

// Library includes
#include "processor.h"

// External includes
#include <vector>

namespace donut
{
	class TDispatcher
	{
	public:
		TDispatcher();
		~TDispatcher();

	public:
		void Reset();
		void ProcessRequests(std::vector<TRenderRequest>& _requests, const Matrix4& _view, const TFrustum& _frusutm);
	protected:
		void UpdateData(std::vector<TRenderRequest>& _requests, const Matrix4& _view);
	protected:
		std::vector<TProcessor*> m_processors;
		std::vector<TBox3> m_vs_bb;
	};
}

#endif // REQUEST_DISPATCHER_H