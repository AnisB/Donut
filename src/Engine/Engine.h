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

#include <base/singleton.h>
#include <Render/Renderer.h>

namespace Donut
{
 	class Engine
 	{
 	public:
 		Engine();
 		~Engine();

 		void LaunchRendering(const TContextDetail& parContext);
 		void StopRendering();

 		void PauseRendering();
 		void ResumeRendering();

 		bool IsRendering();

 		virtual void InitScene(){};


 		virtual void Update(float dt)
 		{
 			glfwPollEvents();
 		}
 		virtual void PrepareNextFrame()
 		{

 		}
 		void SetVertexShader(const std::string& parVertex, int parNbPass = 0);
 		void SetFragmentShader(const std::string& parFrag, int parNbPass = 0);
 		void DrawObject(TDrawableObject * parObject);
 		void RemoveObject(TDrawableObject * parObject);

 	private:
 		THREAD_ID FTRenderingThread;
 		THREAD_DATA FThreadData;
 	protected:
 		TRenderer* FRenderer;
 	};
}
#endif // DONUT_ENGINE