#pragma once

// Library includes
#include "graphics/visualeffect.h"
#include "graphics/light.h"

namespace donut
{
	class TDefferedFX : public TVFX
	{
	public:
		// Creation/Destruction
		TDefferedFX(const GPUBackendAPI* backendAPI);
		virtual ~TDefferedFX();
		// Init
		virtual void Init();
		// Drawing it
		void SetLights(std::vector<TLight>& _lights);
		void Draw(std::map<std::string, TUniform>& _values, const TBufferOutput& _previousData);

	protected:
		TLight* m_lights;
		uint32_t m_nbLights;
	};
}
