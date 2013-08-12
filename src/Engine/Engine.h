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



#ifdef __posix__
#include <pthread.h>
#endif

#include <Base/Singleton.h>
#include <Render/Renderer.h>



 namespace Donut{
 	class Engine : public Singleton<Engine>
 	{
 	public:
 		Engine();
 		~Engine();

 		void LaunchRendering();

 		void StopRendering();

#ifdef __posix__
 		pthread_t FTRenderingThread;
#endif

 	};
 }
 #endif // DONUT_ENGINE