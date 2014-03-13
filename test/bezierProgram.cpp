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
#include <resource/texturehelpers.h>
#include <Render/Representations/3D/Mesh.h>
#include <Render/SceneNode.h>
#include <resource/texture.h>
#include <cmath> 
#define NORMALIZE_VAL 40.0

std::vector<Vector3> controlPoints;
TTexture* controlPointsTexture = NULL;
Donut::TRenderer * window = NULL;
Donut::TMesh* surface = NULL;
Donut::TMesh* surface2 = NULL;
Donut::TMesh* surface3 = NULL;
Donut::DefaultInputManager * inManager = NULL;
Donut::TSceneNode* node;
float totalTime = 0.0;


void generateTexture()
{
	if(controlPointsTexture != NULL)
	{
		delete controlPointsTexture;
	}
	const size_t nbPoints = controlPoints.size();
	if(nbPoints >0)
	{
		controlPointsTexture = new TTexture(5, 5);
		controlPointsTexture->FDataType = TDataType::FLOAT;
		GLfloat * data = new GLfloat[3*controlPoints.size()];
		for(size_t i = 0; i < nbPoints; ++i)
		{
			data[0 + i*3] = PACK_DATA(controlPoints[i].x, NORMALIZE_VAL);
			data[1 + i*3] = PACK_DATA(controlPoints[i].y, NORMALIZE_VAL);
			data[2 + i*3] = PACK_DATA(controlPoints[i].z, NORMALIZE_VAL);
		}		
		controlPointsTexture->FData = (GLvoid*)data;
	}
	TextureHelpers::CreateDataTexture(controlPointsTexture);
}


void updateControlPoint(float dt)
{
	totalTime+=dt;
	controlPoints[13].z = std::cos(totalTime*0.75)*10.0; 
	controlPoints[10].z = std::sin(totalTime*0.5); 
	const size_t nbPoints = controlPoints.size();
	GLfloat * data = (GLfloat *)controlPointsTexture->FData;	
	for(size_t i = 0; i < nbPoints; ++i)
	{
		data[0 + i*3] = PACK_DATA(controlPoints[i].x, NORMALIZE_VAL);
		data[1 + i*3] = PACK_DATA(controlPoints[i].y, NORMALIZE_VAL);
		data[2 + i*3] = PACK_DATA(controlPoints[i].z, NORMALIZE_VAL);
	}		
	controlPointsTexture->FData = (GLvoid*)data;
	TextureHelpers::ReLoadTexture(controlPointsTexture);
}

void createControlPoints()
{
	//
	controlPoints.push_back(Vector3(5,5,5));
	controlPoints.push_back(Vector3(0,5,0));
	controlPoints.push_back(Vector3(0,10,0));
	controlPoints.push_back(Vector3(0,15,0));
	controlPoints.push_back(Vector3(0,20,0));

	controlPoints.push_back(Vector3(5,0,0));
	controlPoints.push_back(Vector3(5,5,-10));
	controlPoints.push_back(Vector3(5,10,0));
	controlPoints.push_back(Vector3(5,15,0));
	controlPoints.push_back(Vector3(5,20,0));

	controlPoints.push_back(Vector3(10,0,0));
	controlPoints.push_back(Vector3(10,5,0));
	controlPoints.push_back(Vector3(10,10,20));
	controlPoints.push_back(Vector3(10,15,0));
	controlPoints.push_back(Vector3(10,20,0));

	controlPoints.push_back(Vector3(15,0,0));
	controlPoints.push_back(Vector3(15,5,0));
	controlPoints.push_back(Vector3(15,10,0));
	controlPoints.push_back(Vector3(15,15,0));
	controlPoints.push_back(Vector3(15,20,0));

	controlPoints.push_back(Vector3(20,0,0));
	controlPoints.push_back(Vector3(20,5,0));
	controlPoints.push_back(Vector3(20,10,0));
	controlPoints.push_back(Vector3(20,15,30));
	controlPoints.push_back(Vector3(20,15,0));
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
	camera->Translate(Vector3(-10,0,0));
}

void initScene()
{
	Donut::TRenderPass* pass= window->GetPasses()[0];
	Donut::TNode* root= pass->GetRoot();

	surface = new Donut::TMesh(TVec3(0,0,-70),"Plane");
	surface->GenerateShader();
	surface2 = new Donut::TMesh(TVec3(30,0,-70),"PlaneLess");
	surface2->GenerateShader();
	surface3 = new Donut::TMesh(TVec3(-30,0,-70),"PlaneMore");
	surface3->GenerateShader();
	createControlPoints();
	generateTexture();
	surface->AddTexture(controlPointsTexture, "controlPoints");
	surface->Init();
	
	surface2->AddTexture(controlPointsTexture, "controlPoints");
	surface2->Init();


	surface3->AddTexture(controlPointsTexture, "controlPoints");
	surface3->Init();

	node = new Donut::TSceneNode();
	node->AddDrawable(surface);
	node->AddDrawable(surface2);
	node->AddDrawable(surface3);
	root->AddChild(node);
	window->RegisterToDraw(surface);
	window->RegisterToDraw(surface2);
	window->RegisterToDraw(surface3);
}
void destroy()
{
	window->UnRegisterToDraw(surface);
	window->UnRegisterToDraw(surface2);
	window->UnRegisterToDraw(surface3);
	delete surface;
	delete surface2;
	delete surface3;
	delete window;
}
void renderLoop()
{
	while(window->IsRendering())
	{
		window->Draw();
		Donut::FarmEvents();
		// node->Pitch(1*0.016);
		updateControlPoint(0.16);
		inManager->Update(0.016);
	}
}


int main()
{
	init();
	initScene();
	renderLoop();
	destroy();
	return 0;
}
