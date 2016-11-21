/**
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU Lesser General Public License as
* published by the Free Software Foundation, either version 3 of the
* License, or (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program. If not, see <http://www.gnu.org/licenses/>.
*
**/


#ifndef SKYBOX_FX_GRAPHICS_DONUT
#define SKYBOX_FX_GRAPHICS_DONUT

// Library includes
#include "graphics/visualeffect.h"
#include "core/camera.h"
#include "core/mesh.h"

namespace Donut
{
	class TSkyboxFX : public TVFX
	{
	public:
		// Creation/Destruction
		TSkyboxFX(const TShader& _shader);
		~TSkyboxFX();
		// Init
		virtual void Init();
		void SetSkybox(SKYBOX_GUID _skybox);
		void SetCamera(Camera* _camera);
		// Drawing it
		void Draw(std::map<std::string, TUniformHandler>& _values, const TBufferOutput& _previousData);
	protected:
		SKYBOX_GUID m_skybox;
		Camera* m_camera;
	};
}

#endif // SKYBOX_FX_GRAPHICS_DONUT
