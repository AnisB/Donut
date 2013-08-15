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
 #include "Math/FloatN.h"
 #include "MultiThread/UsualThreadSafeObjects.h"
 #include <string>

 namespace Donut
 {
	class TDonutRendererOpenGL
	{
	public:
		TDonutRendererOpenGL();
		~TDonutRendererOpenGL();

		void CreateRenderWindow(const float2& parWindowSize, const std::string& parWindowName, bool parIsFullScreen);
		void DestroyRenderWindow();

		void HideRenderWindow();
		void ShowRenderWindow();


		void Draw();
		void Reshape(int, int);

		bool IsRendering()
		{
			return FIsRendering.GetValue();
		}

		void SetRendering(bool parVal)
		{
			FIsRendering.SetValue(parVal);
		}

	protected:
		bool FInitDone;
		int FWindowName;
		bool FIsFullScreen;
		float2 FWindowSize;
		TThreadSafeBolean FIsRendering;

	};
	// END CLASS DECLARATION
	void *CreateRenderingThread(void* parGraphicRenderer);
 }
 #endif // DONUT_GRAPHIC_RENDERER