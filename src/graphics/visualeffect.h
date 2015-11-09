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


#ifndef VISUAL_EFFECT_GRAPHICS_DONUT
#define VISUAL_EFFECT_GRAPHICS_DONUT

// Library includes
#include "graphics/shader.h"
#include "graphics/canvas.h"

namespace Donut
{
	#define CANVAS_VERTEX_SHADER "shaders/canvas/vertex.glsl"
	#define CANVAS_FRAGMENT_SHADER "shaders/canvas/fragment.glsl"
	
	class TVFX
	{
	public:
		// Creation/Destruction
		TVFX(const TShader& _shader);
		virtual ~TVFX();
		// Init
		virtual void Init();
		// Drawing it
		virtual void Draw(const TBufferOutput& _previous) = 0;
		// Attaching a texture to a vfx
	 	virtual void AddTexture(TTexture* _texture, const std::string& _nameInMaterial);
	protected:
		void BindBufferOutput(const TBufferOutput& _previous);
	protected:
		// Material
		TMaterial m_material;
		// Geometry
		TGeometry* m_fsq;
	};
}


#endif // VISUAL_EFFECT_GRAPHICS_DONUT
