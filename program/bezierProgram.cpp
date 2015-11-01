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

// Autres includes
#include <cmath> 

// Declaration de constantes
// Normalize val permet de définir la valeur maximale (en valeur absolue que vont avoir les coordonnées xyz de chaque point)
// Elle sert a normalize les valeur avant de les injecter dans la texture
#define NORMALIZE_VAL 40.0

// Liste des points de contorle
std::vector<Donut::Vector3> controlPoints;
// La texture de points de controle
TTexture* controlPointsTexture = NULL;
// La fenetre de rendu
Donut::TRenderer * window = NULL;
// Les surface a afficher
Donut::TMesh *surface1, * surface2 = NULL, *surface3 = NULL;
// Le gestionnaire d'input
Donut::TDefaultInputManager * inManager = NULL;
// Noeud de scene principal
Donut::TSceneNode *node1,*node2,*node3;
//Temps global
float totalTime = 0.0;
// Resolution de la grille
#define RESOLUTION_GRID 5 

using namespace Donut;
//Génére la texture la première fois
void generateTexture()
{
	// Le nombre de point de controle
	const size_t nbPoints = controlPoints.size();
	if(nbPoints >0)
	{
		// Création de la texture
		controlPointsTexture = new TTexture(RESOLUTION_GRID, RESOLUTION_GRID);
		// Definition du type de données stockées dans cette texture
		controlPointsTexture->FDataType = TDataType::FLOAT;
		// Allocation de la mémoire nécessaire au stockage de la texture
		GLfloat * data = new GLfloat[3*controlPoints.size()];
		// Copie des données dans le tableau
		for(size_t i = 0; i < nbPoints; ++i)
		{
			// PACK_DATA normalize les données entre [0,1] pour qu'il n'y ai pas de pertes 
			data[0 + i*3] = PACK_DATA(controlPoints[i].x, NORMALIZE_VAL);
			data[1 + i*3] = PACK_DATA(controlPoints[i].y, NORMALIZE_VAL);
			data[2 + i*3] = PACK_DATA(controlPoints[i].z, NORMALIZE_VAL);
		}		
		controlPointsTexture->FData = (GLvoid*)data;
	}
	// Injection de la texture dans la mémoire
	TextureHelpers::CreateDataTexture(controlPointsTexture);
}


void updateControlPoint(float dt)
{
	// Mise a jours du temps total
	totalTime+=dt;
	//totalTime =fmod(totalTime,2.0*PI);
	// Deplacement des deux points de controle qui modifie la forme de la surface
	controlPoints[13].z = std::cos(totalTime*0.75)*10.0; 
	controlPoints[10].z = std::sin(totalTime*0.5); 
	// Mise a jour des points de controle dans la texture
	const size_t nbPoints = controlPoints.size();
	GLfloat * data = (GLfloat *)controlPointsTexture->FData;	
	for(size_t i = 0; i < nbPoints; ++i)
	{
		// PACK_DATA normalize les données entre [0,1] pour qu'il n'y ai pas de pertes 
		data[0 + i*3] = PACK_DATA(controlPoints[i].x, NORMALIZE_VAL);
		data[1 + i*3] = PACK_DATA(controlPoints[i].y, NORMALIZE_VAL);
		data[2 + i*3] = PACK_DATA(controlPoints[i].z, NORMALIZE_VAL);
	}		
	controlPointsTexture->FData = (GLvoid*)data;
	// Reinjection des points dans la mémoire GPu
	TextureHelpers::ReLoadTexture(controlPointsTexture);
}

void createControlPoints()
{
	// Creation de tout les points de controle
	controlPoints.push_back(Donut::vector3(5,5,5));
	controlPoints.push_back(Donut::vector3(0,5,0));
	controlPoints.push_back(Donut::vector3(0,10,0));
	controlPoints.push_back(Donut::vector3(0,15,0));
	controlPoints.push_back(Donut::vector3(0,20,0));

	controlPoints.push_back(Donut::vector3(5,0,0));
	controlPoints.push_back(Donut::vector3(5,5,-10));
	controlPoints.push_back(Donut::vector3(5,10,0));
	controlPoints.push_back(Donut::vector3(5,15,0));
	controlPoints.push_back(Donut::vector3(5,20,0));

	controlPoints.push_back(Donut::vector3(10,0,0));
	controlPoints.push_back(Donut::vector3(10,5,0));
	controlPoints.push_back(Donut::vector3(10,10,20));
	controlPoints.push_back(Donut::vector3(10,15,0));
	controlPoints.push_back(Donut::vector3(10,20,0));

	controlPoints.push_back(Donut::vector3(15,0,0));
	controlPoints.push_back(Donut::vector3(15,5,0));
	controlPoints.push_back(Donut::vector3(15,10,0));
	controlPoints.push_back(Donut::vector3(15,15,0));
	controlPoints.push_back(Donut::vector3(15,20,0));

	controlPoints.push_back(Donut::vector3(20,0,0));
	controlPoints.push_back(Donut::vector3(20,5,0));
	controlPoints.push_back(Donut::vector3(20,10,0));
	controlPoints.push_back(Donut::vector3(20,15,30));
	controlPoints.push_back(Donut::vector3(20,15,0));
}


void init()
{
	// Spécifie le répertoire de chargement des modèles
    Donut::TSugarLoader::Instance().Init("data");    
	// Creating the rendering window
	window = new Donut::TRenderer();

	// Context info
	Donut::TGraphicsSettings newContext;
	newContext.windowName = "bezierProgram";
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
	camera->Translate(Donut::vector3(-10,0,0));
}

void initScene()
{
	Donut::TRenderPass* pass= window->GetPasses()[0];
	Donut::TNode* root= pass->GetRoot();

	// On crée la surface 1 à la position vector3(0,0,-70) en utilisant le modèle de nom "Plane"
	surface1 = new Donut::TMesh("Plane");
	surface2 = new Donut::TMesh("PlaneLess");
	surface3 = new Donut::TMesh("PlaneMore");
	// On crée les points de controle
	createControlPoints();
	// On génère la texture qui contiendra ces points de controle
	generateTexture();
	
	// On l'injecte dans chacun des modèles
	surface1->AddTexture(controlPointsTexture, "controlPoints");
	surface2->AddTexture(controlPointsTexture, "controlPoints");
	surface3->AddTexture(controlPointsTexture, "controlPoints");
	
	// On crée un noeud de scene
	node1 = new Donut::TSceneNode();
	node1->Translate(vector3(0,0,-70));
	node2 = new Donut::TSceneNode();
	node2->Translate(vector3(30,0,-70));
	node3 = new Donut::TSceneNode();
	node3->Translate(vector3(-30,0,-70));
	// On lui ajoute chacun des drawable
	node1->AddDrawable(surface1);
	node2->AddDrawable(surface2);
	node3->AddDrawable(surface3);
	// On ajoute le noeud créé au noeud racine
	root->AttachChild(node1);
	root->AttachChild(node2);
	root->AttachChild(node3);
	// Petite acceleration qui permet de mettre a jour les donées uniformes pour un cout minimal
	window->RegisterToDraw(surface1);
	window->RegisterToDraw(surface2);
	window->RegisterToDraw(surface3);
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
		double delta = inManager->Update();
		updateControlPoint(delta);
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
