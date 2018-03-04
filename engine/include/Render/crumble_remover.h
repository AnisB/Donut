#ifndef CRUMBLE_REMOVER_H
#define CRUMBLE_REMOVER_H

// Library includes
#include "processor.h"
#include "render_request.h"
#include "core/frustum.h"
#include "core/box3.h"

namespace donut
{
	// This class is able to remove request that are considered too small
	class TCrumbleRemover : public TProcessor
	{
	public:
		// Cst and Dst
		TCrumbleRemover();
		~TCrumbleRemover();

		void Process(std::vector<TRenderRequest>& _requests, std::vector<TBox3>& _vsBoxes, const bento::Matrix4& _view, const TFrustum& _frusutm);

	protected:
		std::vector<char> m_discardArray;
	};
}
#endif // CRUMBLE_REMOVER_H