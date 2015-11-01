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

std::vector<Vector3> gridPoints;
// La fenetre de rendu
Donut::TRenderer * window = NULL;
// Le gestionnaire d'input
Donut::TDefaultInputManager * inManager = NULL;
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
	Donut::TGraphicsSettings newContext;
	newContext.windowName = "marchingCubes";
	//Initialisation de la fenetre
	window->CreateRenderWindow(newContext);
	window->Init();

	// Getting the camera
	Donut::Camera* camera = window->GetCamera();
	// On définit un gestionnaire d'input
	inManager = new Donut::TDefaultInputManager();
	Donut::SetInputManager(inManager);
	// On donne la camera a l'input manager
	inManager->FCamera = camera;
	// On définit la perspective
	camera->DefinePerspective(45.0,1280.0/720.0,1.0,500.0);
	// On déplace la camera
	camera->Translate(Vector3(-10,0,0));
}

void initScene()
{
	Donut::TRenderPass* pass= window->GetPasses()[0];
	Donut::TNode* root= pass->GetRoot();

}
// Fonction de destruction
void destroy()
{
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
