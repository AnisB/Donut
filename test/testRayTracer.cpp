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
#include <Render/SceneNode.h>
#include <resource/texture.h>
#include <resource/resourcemanager.h>

// Autres includes
#include <cmath> 

// Declaration de constantes
// Normalize val permet de définir la valeur maximale (en valeur absolue que vont avoir les coordonnées xyz de chaque point)
// Elle sert a normalize les valeur avant de les injecter dans la texture
#define NORMALIZE_VAL 40.0

// La texture de points de controle
TTexture* triangles = NULL;
// La fenetre de rendu
Donut::TRenderer * window = NULL;
// Les surface a afficher
Donut::TMesh* surface = NULL;
// Le gestionnaire d'input
Donut::DefaultInputManager * inManager = NULL;
// Noeud de scene principal
Donut::TSceneNode* node;

void init()
{
	// Spécifie le répertoire de chargement des modèles
	Donut::TSugarLoader& modeltest = Donut::TSugarLoader::Instance();	
	modeltest.SetDirectory("data");
	// Charge les modèles
	modeltest.LoadSugars();
	// Creating the rendering window
	window = new Donut::TRenderer();

	// Context info
	Donut::TContextDetail newContext;
	newContext.windowName = "bezierProgram";
	//Initialisation de la fenetre
	window->CreateRenderWindow(newContext);
	window->Init();

	// Getting the camera
	Donut::Camera* camera = window->GetCamera();
	// On définit un gestionnaire d'input
	inManager = new Donut::DefaultInputManager();
	Donut::SetInputManager(inManager);
	// On donne la camera a l'input manager
	inManager->FCamera = camera;
	// On définit la perspective
	camera->DefinePerspective(45.0,1280.0/720.0,1.0,500.0);
	// On déplace la camera
	camera->Translate(Vector3(0,0,-20));
}

void initScene()
{
	Donut::TRenderPass* pass= window->GetPasses()[0];
	Donut::TNode* root= pass->GetRoot();

	// On crée la surface 1 à la position TVec3(0,0,-70) en utilisant le modèle de nom "Plane"
	surface = new Donut::TMesh(TVec3(0, 0, 0),"FSQuad");
	// On génère le shader associé a ce modèle
	surface->GenerateShader();
	// On crée les points de controle
	// std::vector<TTexture*> triangles = Donut::ResourceManager::Instance().LoadObjToTexture("data/models/other/triangle.obj");
	std::vector<TTexture*> triangles = Donut::ResourceManager::Instance().LoadObjToTexture("data/models/lego/legodude.obj");
	TextureHelpers::CreateDataTexture(triangles[0]);
	// On l'injecte dans chacun des modèles
	surface->AddTexture(triangles[0], "triangles");
	surface->Init();
	// On crée un noeud de scene
	node = new Donut::TSceneNode();
	// On lui ajoute chacun des drawable
	node->AddDrawable(surface);
	// On ajoute le noeud créé au noeud racine
	root->AddChild(node);
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
