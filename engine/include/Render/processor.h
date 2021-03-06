#ifndef REQUEST_PROCESSOR_H
#define REQUEST_PROCESSOR_H

// Bento includes
#include <bento_math/types.h>


// External includes
#include <vector>

namespace donut
{
	// Foward declare
	struct TRenderRequest;
	struct Matrix4;
	struct TBox3;
	class TFrustum;

	class TProcessor
	{
	public:
		TProcessor() {}
		virtual ~TProcessor() {}
	public:
		virtual void Process(std::vector<TRenderRequest>& _requests, std::vector<TBox3>& _vsBoxes, const bento::Matrix4& _view, const TFrustum& _frusutm) = 0;
	};
}

#endif // REQUEST_PROCESSOR_H