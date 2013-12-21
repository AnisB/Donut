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
 #include <Math/int.h>
 #include "multithread/usualthreadsafeobjects.h"
 #include <string>
 #include <vector>




 namespace Donut
 {

 	#define DEFAULT_NB_PASSES 1

	class TRenderer
	{
	public:
		TRenderer();
		~TRenderer();

		bool CreateRenderWindow(const TContextDetail& parContext, size_t parNbPass = DEFAULT_NB_PASSES);
		void DestroyRenderWindow();

		void HideRenderWindow();
		void ShowRenderWindow();


		bool Init();
		void Draw();
		void Clear();

		void RegisterToDraw(TDrawableObject * parDrawable, size_t PASS_NUMBER = 0);
		void UnRegisterToDraw(TDrawableObject * parDrawable, size_t PASS_NUMBER = 0);

		// Rendering activation and disable
		bool IsRendering();
		void SetRendering(bool parVal);


 		void SetRenderType(FrameCanvasContent::Type parType, int parNbPass = 0);
 		void SetVertexShader(const std::string& parVertex, int parNbPass = 0);
 		void SetFragmentShader(const std::string& parFrag, int parNbPass = 0);
 		std::vector<TRenderPass*>& GetPasses(){return FRenderPasses;}

 	private:
 		void InputInit();

	protected:

		// Window Infos
		bool FInitDone;
		GLFWwindow * FWindow;
		bool FIsFullScreen;
		TInt2 FWindowSize;
		size_t FNbPasses;

		// Is Rendering member
		TThreadSafeBolean FIsRendering;

		std::vector<TRenderPass*> FRenderPasses;

	};
	// END CLASS DECLARATION



	void *CreateRenderingThread(void* parGraphicRenderer);
 }
 #endif // DONUT_GRAPHIC_RENDERER