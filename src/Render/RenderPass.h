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


#include "DrawableObject.h"

#include <MultiThread/ThreadSharedObject.h>
#include <Render/Camera.h>
#include "Node.h"

#include "FrameCanvas.h"

#include <list>
 
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
		void AddDrawable(TDrawableObject* parDrawable);
		void RemoveDrawable(TDrawableObject* parDrawable);

		void SetFragmentShader(const std::string& parFShader);
		void SetVertexShader(const std::string& parVShader);
		void PreparePass();
		void IsFramedCanvas(bool parVal)
		{
			FRenderToTexture = parVal;
		}
		Camera* GetCamera(){return FCamera;}
		void SetRenderType(FrameCanvasContent::Type parType);
		TNode* GetRoot();
	private:
		void Bind();
		void Unbind();

	private:
		TFrameCanvas * FFrameCanvas;
		Camera * FCamera;

		bool FRenderToTexture;

	protected:
		TNode* FRoot;
		std::list<TDrawableObject*> FDrawables;
	};
	// END CLASS DECLARATION
 }
 #endif // DONUT_2D_RENDER_PASS
