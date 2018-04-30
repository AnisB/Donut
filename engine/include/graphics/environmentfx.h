#pragma once

// Library includes
#include "graphics/visualeffect.h"
#include "graphics/sphericalharmonics.h"

namespace donut
{
	class TEnvironmentFX : public TVFX
	{
	public:
		// Creation/Destruction
		TEnvironmentFX();
		virtual ~TEnvironmentFX();

		// Init
		virtual void Init();
		// Drawing it
		void SetSH(TSphericalHarmonics* _SH) {m_SH = _SH;}
		void Draw(std::map<std::string, TUniform>& _values, const TBufferOutput& _previousData);

	protected:
		TSphericalHarmonics* m_SH;
	};
}