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


#include "Renderer.h"

#include "Base/Common.h"

#include "GL/glut.h"
#include "GL/gl.h"

namespace Donut
{

	// Class TDonutRendererOpenGL
	TDonutRendererOpenGL::TDonutRendererOpenGL()
		: FWindowSize(float2())
		, FIsFullScreen(false)
		, FWindowName(-1)
		, FIsRendering(false)
		, FInitDone(false)
	{

	}
	TDonutRendererOpenGL::~TDonutRendererOpenGL()
	{

	}

	void TDonutRendererOpenGL::CreateRenderWindow(const float2& parWindowSize, const std::string& parWindowName, bool parIsFullScreen)
	{
		if(!FInitDone)
		{
	 		RENDER_DEBUG_NOARGS("Creating window");

		  	int argc = 1;
		  	char *argv[1] = {(char*)"Donuts are fucking awesome"};
			// Init
		 	glutInit(&argc, argv);

		 	//DisplayMode
			glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);

			// Window size
			
			glutInitWindowSize(FWindowSize.x, FWindowSize.y);

			//CreateWindow
			FWindowName = glutCreateWindow(parWindowName.c_str());

			if(FIsFullScreen)
			{
				glutFullScreen();
			}
			FIsRendering.SetValue(true);
	 		RENDER_DEBUG_NOARGS("Window created");

		}
		else
		{
	 		RENDER_DEBUG_NOARGS("This window has already been created.");
			AssertRelease(FWindowName != -1);
			glutShowWindow();
		}
	}
	void TDonutRendererOpenGL::HideRenderWindow()
	{
 		RENDER_DEBUG_NOARGS("Hiding window.");	
		AssertRelease(FWindowName != -1);
		glutHideWindow();
	}	

	void TDonutRendererOpenGL::ShowRenderWindow()
	{
 		RENDER_DEBUG_NOARGS("Showing window.");	
		AssertRelease(FWindowName != -1);
		glutShowWindow();
	}	

	void TDonutRendererOpenGL::DestroyRenderWindow()
	{
 		RENDER_DEBUG_NOARGS("Destroying window.");	
		AssertRelease(FWindowName != -1);
		glutHideWindow();
		glutDestroyWindow(FWindowName);
		FWindowName = -1;
		FInitDone = false;

	}	

	void TDonutRendererOpenGL::Draw()
	{ 	 	
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 	//Efface le frame buffer et le Z-buffer
		glMatrixMode(GL_MODELVIEW); 	//Choisit la matrice MODELVIEW
		glLoadIdentity(); 	//Réinitialise la matrice
		gluLookAt(0,0,-10,0,0,0,0,1,0);

		glEnd(); 

		glutSwapBuffers();

		glutPostRedisplay();
			//Demande de recalculer la scène

	}


	void TDonutRendererOpenGL::Reshape(int width, int height)
	{ 	 
	  	glViewport(0,0,width,height);
	  	glMatrixMode(GL_PROJECTION);
	  	glLoadIdentity();
	  	gluPerspective(45,float(width)/float(height),0.1,100); 	
	  	glMatrixMode(GL_MODELVIEW);
	}



		// END CLASS DECLARATION
	void *CreateRenderingThread(void* parGraphicRenderer)
 	{
 		TDonutRendererOpenGL * realGraphicRenderer = (TDonutRendererOpenGL*) parGraphicRenderer;
 		while(realGraphicRenderer->IsRendering())
 		{
 	    	realGraphicRenderer->Draw();
 	    }
 		pthread_exit(0);
 	}
 	 
}
