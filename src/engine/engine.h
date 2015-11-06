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


#ifndef DONUT_ENGINE
#define DONUT_ENGINE

// Donut includes
#include <input/inputhelper.h>
#include <Render/Renderer.h>

namespace Donut
{
 	class TEngine
 	{
 	public:
 		TEngine();
 		~TEngine();
 		void LaunchRendering(const TGraphicsSettings& parContext);
 		void StopRendering();
 		void PauseRendering();
 		void ResumeRendering();
 		bool IsRendering();
 		virtual void InitScene() {}
 		// Please call the mother Update function
 		// in your implementation of the rendering engine
 		virtual void Update(float dt);
 		virtual void PrepareNextFrame() {}
 		void SetShader(const TShader& _shader, int parNbPass = 0);
 		void DrawObject(TDrawable * parObject);
 		void RemoveObject(TDrawable * parObject);

 	private:
 		// Data required to launch the rendering thread
 		THREAD_ID FTRenderingThread;
 		THREAD_DATA FThreadData;
 		bool FRenderingRunning;
 	protected:
 		// A pointer to the renderer
 		TRenderer* FRenderer;
 	};
}
#endif // DONUT_ENGINE