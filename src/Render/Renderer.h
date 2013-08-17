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


 #ifndef DONUT_GRAPHIC_RENDERER
 #define DONUT_GRAPHIC_RENDERER

 #include "Defines.h"
 #include "RenderPass.h"
 #include "Math/FloatN.h"
 #include "MultiThread/UsualThreadSafeObjects.h"
 #include <string>




 namespace Donut
 {

 	#define NB_PASSES 1

	class TDonutRendererOpenGL
	{
	public:
		TDonutRendererOpenGL();
		~TDonutRendererOpenGL();

		void CreateRenderWindow(const float2& parWindowSize, const std::string& parWindowName, bool parIsFullScreen);
		void DestroyRenderWindow();

		void HideRenderWindow();
		void ShowRenderWindow();


		void Init();
		void Draw();
		void Clear();

		void RegisterToDraw(TDrawableObject * parDrawable, size_t PASS_NUMBER = 0);

		// Rendering activation and disable
		bool IsRendering();
		void SetRendering(bool parVal);

	protected:

		// Window Infos
		bool FInitDone;
		GLFWwindow * FWindow;
		bool FIsFullScreen;
		float2 FWindowSize;

		// Is Rendering member
		TThreadSafeBolean FIsRendering;

		TRenderPass FRenderPasses[NB_PASSES];

	};
	// END CLASS DECLARATION



	void *CreateRenderingThread(void* parGraphicRenderer);
 }
 #endif // DONUT_GRAPHIC_RENDERER