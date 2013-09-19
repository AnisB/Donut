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


#include "DrawableObject.h"
#include "ShaderManager.h"

#include "MultiThread/ThreadSharedObject.h"

 
 namespace Donut
 {

	class TFrameCanvas :  public TDrawableObject, public TThreadSharedObject
	{
	public:
		TFrameCanvas();
		~TFrameCanvas();

		void Init();

		void SetFragmentShader(const std::string& parFShader);
		void SetVertexShader(const std::string& parVShader);
		
		virtual void Draw();
		void Enable();
		void Disable();
	protected:

		// Buffer Data
		GLuint FFrameBuffer;
		GLuint FRenderTexture;
		GLuint FDepthBuffer;

		//Shader
		TShader FShader;

	};
	// END CLASS DECLARATION
 }
 #endif // DONUT_FRAME_CANVAS
