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


 #ifndef DONUT_2D_RENDER_PASS
 #define DONUT_2D_RENDER_PASS


#include "graphics/drawable.h"

#include <MultiThread/ThreadSharedObject.h>
#include "core/Camera.h"
#include "core/node.h"
 
#include "Render/Light.h"

#include "FrameCanvas.h"

#include <vector>
 
 namespace Donut
 {

	class TRenderPass : public TThreadSharedObject
	{
	public:
		TRenderPass();
		~TRenderPass();
		void Init();

		void Draw();
		void Clear();

		void AddLight(TLight* parLight);
		void RemoveLight(TLight* parLight);

		void AddDrawable(TDrawable* parDrawable);
		void RemoveDrawable(TDrawable* parDrawable);

		void SetFragmentShader(const std::string& parFShader);
		void SetVertexShader(const std::string& parVShader);
		void PreparePass();
		void IsFramedCanvas(bool parVal)
		{
			FRenderToTexture = parVal;
		}
		void SetRenderType(FrameCanvasContent::Type parType);
		TNode* GetRoot();
		Camera* GetCamera(){return FCamera;}

		void AddTexture(const std::string& _textureName, const std::string& _unifomName);
		
	private:
		void Bind();
		void Unbind();

	private:
		TFrameCanvas * FFrameCanvas;
		Camera * FCamera;

		bool FRenderToTexture;

	protected:
		TNode* FRoot;
		std::vector<TDrawable*> FDrawables;
		std::vector<TLight*> FLights;
	};
	// END CLASS DECLARATION
 }
 #endif // DONUT_2D_RENDER_PASS
