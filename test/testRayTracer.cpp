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

//Includes engine
#include <Render/Renderer.h>
#include <base/common.h>
#include <Input/InputHelper.h>
#include <Input/DefaultInputManager.h>
#include <resource/sugarloader.h>
#include <resource/texturehelpers.h>
#include <Render/Representations/3D/Mesh.h>
#include <core/SceneNode.h>
#include <resource/texture.h>
#include <resource/resourcemanager.h>

// Autres includes
#include <cmath> 

using namespace Donut;

// La texture de points de controle
TTexture* triangles = NULL;
// La fenetre de rendu
Donut::TRenderer * window = NULL;
// Les surface a afficher
Donut::TMesh* surface = NULL;
// Le gestionnaire d'input
Donut::TDefaultInputManager * inManager = NULL;
// Noeud de scene principal
Donut::TSceneNode* node;

void init()
{
	// Spécifie le répertoire de chargement des modèles
	Donut::TSugarLoader::Instance().Init("data");	
	// Creating the rendering window
	window = new Donut::TRenderer();

	// Context info
	Donut::TGraphicsSettings newContext;
	newContext.windowName = "bezierProgram";
	newContext.width = 512;
	newContext.lenght = 386;
	//Initialisation de la fenetre
	window->CreateRenderWindow(newContext);
	window->Init();

	// Getting the camera
	Donut::Camera* camera = window->GetCamera();
	// On définit un gestionnaire d'input
	Donut::TDefaultInputManager* inManager = static_cast<Donut::TDefaultInputManager*>(Donut::GetInputManager());
	inManager->FCamera = camera;
	// On définit la perspective
	camera->DefinePerspective(29.0,1280.0/720.0,1.0,500.0);
	// On déplace la camera
	camera->Translate(Donut::vector3(0,0,-20));
}

void initScene()
{
	Donut::TRenderPass* pass= window->GetPasses()[0];
	Donut::TNode* root= pass->GetRoot();

	// On crée la surface 1 à la position TVec3(0,0,-70) en utilisant le modèle de nom "Plane"
	surface = new Donut::TMesh("FSQuad");
	// On génère le shader associé a ce modèle
	// On crée les points de controle
	// std::vector<TTexture*> triangles = Donut::ResourceManager::Instance().LoadObjToTexture("data/models/teapot/model.obj");
	// std::vector<TTexture*> triangles = Donut::ResourceManager::Instance().LoadObjToTexture("data/models/test/cube.obj");
	std::vector<TTexture*> triangles;
	std::vector<int> nbShapes = Donut::ResourceManager::Instance().LoadObjToTexture("data/geometry/teapot.obj",triangles);
	TextureHelpers::CreateDataTexture(triangles[0]);
	// On l'injecte dans chacun des modèles
	surface->AddTexture(triangles[0], "triangles");
	// On crée un noeud de scene
	node = new Donut::TSceneNode();
	// On lui ajoute chacun des drawable
	node->AddDrawable(surface);
	// On ajoute le noeud créé au noeud racine
	root->AttachChild(node);
	// Petite acceleration qui permet de mettre a jour les donées uniformes pour un cout minimal
	window->RegisterToDraw(surface);
}
// Fonction de destruction
void destroy()
{
	window->UnRegisterToDraw(surface);
	delete window;
}
// Loop de rendu
void renderLoop()
{

	while(window->IsRendering())
	{
		window->Draw();
		Donut::FarmEvents();
		inManager->Update();
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
