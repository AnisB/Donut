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

#include <Render/Renderer.h>
#include <base/common.h>
#include <Input/InputHelper.h>
#include <Input/DefaultInputManager.h>
#include <resource/sugarloader.h>
#include <Render/Representations/3D/Mesh.h>
#include <Render/SceneNode.h>
#include <resource/texture.h>

#define NORMALIZE_VAL 1000

std::vector<Vector3> controlPoints;
TTexture* controlPointsTex = NULL;
Donut::TRenderer * window = NULL;
Donut::TDrawableObject* surface = NULL;
Donut::DefaultInputManager * inManager = NULL;


void generateTexture()
{
	if(controlPointsTex != NULL)
	{
		delete controlPointsTex;
	}
	const size_t nbPoints = controlPoints.size();
	if(nbPoints >0)
	{
		controlPointsTex = new TTexture(3, nbPoints);
		controlPointsTex->FDataType = TDataType::FLOAT;
		GLfloat * data = new GLfloat[3*controlPoints.size()];
		for(size_t i = 0; i < nbPoints; ++i)
		{
			data[0 + i*3] = PACK_DATA(controlPoints[i].x, NORMALIZE_VAL);
			data[1 + i*3] = PACK_DATA(controlPoints[i].y, NORMALIZE_VAL);
			data[2 + i*3] = PACK_DATA(controlPoints[i].z, NORMALIZE_VAL);
		}		
		controlPointsTex->FData = (GLvoid*)data;
	}
}


void init()
{
	Donut::TSugarLoader& modeltest = Donut::TSugarLoader::Instance();	
	modeltest.SetDirectory("data");
	modeltest.LoadSugars();
	// Creating the rendering window
	window = new Donut::TRenderer();

	// Context info
	Donut::TContextDetail newContext;
	newContext.windowName = "nurbsProgram";
	window->CreateRenderWindow(newContext);
	window->Init();

	// Getting the camera
	Donut::TRenderPass* pass= window->GetPasses()[0];
	Donut::Camera* camera = pass->GetCamera();
	inManager = new Donut::DefaultInputManager();
	Donut::SetInputManager(inManager);
	inManager->FCamera = camera;
	camera->DefinePerspective(45.0,1280.0/720.0,1.0,500.0);
}

void initScene()
{
	Donut::TRenderPass* pass= window->GetPasses()[0];
	Donut::TNode* root= pass->GetRoot();

	surface = new Donut::TMesh(TVec3(0,0,-40),"Plane");
	surface->GenerateShader();
	surface->Init();
	
	Donut::TSceneNode* node = new Donut::TSceneNode();
	node->AddDrawable(surface);
	root->AddChild(node);
	window->RegisterToDraw(surface);
}
void destroy()
{
	window->UnRegisterToDraw(surface);
	delete surface;
	delete window;
}
void renderLoop()
{
	while(window->IsRendering())
	{
		window->Draw();
		Donut::FarmEvents();
		inManager->Update(0.016);
	}
}

void createControlPoints()
{

}

int main()
{
	init();
	initScene();
	renderLoop();
	destroy();
	return 0;
}
