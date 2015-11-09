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


 #ifndef DONUT_FRAME_CANVAS
 #define DONUT_FRAME_CANVAS


#include "graphics/drawable.h"
#include "graphics/shaderManager.h"
#include "graphics/mesh.h"
#include "graphics/material.h"
#include <Render/Light.h>
#include <resource/texture.h>
#include "MultiThread/ThreadSharedObject.h"

#include <vector>
 
 namespace Donut
 {
 	namespace FrameCanvasContent
 	{
 		enum Type
 		{
 			STANDARD, // DIFF+DEPTH
 			DEFFERED // Deferred lightning
 		};
 	}

	class TFrameCanvas
	{
	public:
		TFrameCanvas();
		~TFrameCanvas();

		void Init();

		void SetType(FrameCanvasContent::Type parType)
		{
			FCanvasType = parType;
		}
		void SetShader(const TShader& _shader);

		virtual void Draw(const std::vector<TLight*>& parLights);
		void InjectData(const TShader& parShader);

		void Enable();
		void EnableSecond();
		void Disable();
		void AttachTexture(TTexture* _texture, const std::string& _uniformVarName);

	protected:
		void CreateShader();
	protected:

		// Buffer Data
		GLuint FFrameBuffer;
		FrameCanvasContent::Type FCanvasType;

		// Gbuffer data, should be moved to the material
		TTextureInfo m_buffers[5];
		// Textures, should be moved to the Material
		std::vector<TTexture*> FTextures;
		int FTextureCounter;

		// Quad
	 	TGeometry* m_fsq;
		//Shader
		TMaterial FMaterial;
	};
	// END CLASS DECLARATION
 }
 #endif // DONUT_FRAME_CANVAS
