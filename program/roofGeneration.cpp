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
#include <Input/InputHelper.h>
#include <Input/DefaultInputManager.h>
#include <Input/InputManager.h>
#include <resource/sugarloader.h>
#include <Render/Common.h>
#include <Render/SceneNode.h>
#include <Render/Representations/3D/Mesh.h>
#include <Interface.h>
#include <Resource/model.h>
#include <Render/ShaderManager.h>
#include <Math/helper.h>

TModel* ComputeModel( CityGeneration::TMesh* _mesh, const Donut::TShader& parShader)
{
	TModel* newModel = new TModel();
	
	GLuint VAO;
	glGenVertexArrays (1, &VAO);
	glBindVertexArray (VAO);

	GLuint VBO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GL_FLOAT)*_mesh->nbVerts*3, _mesh->pos, GL_STATIC_DRAW);
	GLuint posAtt = glGetAttribLocation(parShader.FProgramID, "position");
	glEnableVertexAttribArray (posAtt);
	glVertexAttribPointer (posAtt, 3, GL_FLOAT, GL_FALSE, 0, 0);

	GLuint IBO;
	glGenBuffers(1, &IBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int)*_mesh->nbFaces*3, _mesh->index, GL_STATIC_DRAW);

	GLuint FBO;
	glGenBuffers(1, &FBO);
	glBindBuffer(GL_ARRAY_BUFFER, FBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GL_FLOAT)*_mesh->nbVerts*3, _mesh->normal, GL_STATIC_DRAW);
	GLuint normalAtt = glGetAttribLocation(parShader.FProgramID, "normal");
	glEnableVertexAttribArray (normalAtt);
	glVertexAttribPointer (normalAtt, 3, GL_FLOAT, GL_FALSE, 0, 0);

	newModel->vertexArray = VAO;
	newModel->nbVertices = _mesh->nbFaces*3;

	return newModel;
}

Donut::TDrawableObject* GenerateDrawableMeshFromPoints( CityGeneration::TInputProfile& _input)
{
	CityGeneration::TMesh* mesh =  CityGeneration::generateBuilding(_input);
	Donut::TShader shader;
	shader.FVertexShader = "shaders/uniform/vertex.glsl";
	shader.FFragmentShader = "shaders/uniform/fragment.glsl";
	Donut::ShaderManager::Instance().CreateShader(shader);
	TModel* model = ComputeModel(mesh, shader);
	Donut::TMesh* hat = new Donut::TMesh(shader,model);
	return hat;
}


int main()
{
	std::vector< CityGeneration::TInputProfile*> flatHouses;
	
	{
		 CityGeneration::TInputProfile* house = new  CityGeneration::TInputProfile();
		 CityGeneration::TContour* contour = new  CityGeneration::TContour();
		contour->type =  CityGeneration::TContourType::OUTER;
		contour->points.push_back(stingray::vector3(-200.0, -100.0,0.0));
		contour->points.push_back(stingray::vector3(-50.0, -100.0,0.0));
		contour->points.push_back(stingray::vector3(-50.0, -150.0,0.0));
		contour->points.push_back(stingray::vector3(50, -150,0.0));
		contour->points.push_back(stingray::vector3(50, -100.0,0.0));
		contour->points.push_back(stingray::vector3(200, -100.0,0.0));
		contour->points.push_back(stingray::vector3(200.0, 100.0,0.0));
		contour->points.push_back(stingray::vector3(-200.0, 100.0,0.0));
		house->AddContour(contour);
		house->AddParameter("H", 100.0);
		house->SetProfile( CityGeneration::TOSMProfile::FLAT);
		flatHouses.push_back(house);
	}
	
	
	{
		 CityGeneration::TInputProfile* house = new  CityGeneration::TInputProfile();
		{
			 CityGeneration::TContour* contour = new  CityGeneration::TContour();
			contour->type =  CityGeneration::TContourType::OUTER;
			contour->points.push_back(stingray::vector3(-200.0, -100.0,0.0));
			contour->points.push_back(stingray::vector3(-50.0, -100.0,0.0));
			contour->points.push_back(stingray::vector3(-50.0, -150.0,0.0));
			contour->points.push_back(stingray::vector3(50, -150,0.0));
			contour->points.push_back(stingray::vector3(50, -100.0,0.0));
			contour->points.push_back(stingray::vector3(200, -100.0,0.0));
			contour->points.push_back(stingray::vector3(200.0, 100.0,0.0));
			contour->points.push_back(stingray::vector3(-200.0, 100.0,0.0));
			house->AddContour(contour);
		}
		{
			 CityGeneration::TContour* contour = new  CityGeneration::TContour();
			contour->type =  CityGeneration::TContourType::INNER;
			contour->points.push_back(stingray::vector3(-150, -50.0,0.0));
			contour->points.push_back(stingray::vector3(-150, 50.0,0.0));
			contour->points.push_back(stingray::vector3(150, 50.0,0.0));
			contour->points.push_back(stingray::vector3(150, -50.0,0.0));
			house->AddContour(contour);
		}
		house->AddParameter("H", 100.0);
		house->AddParameter("H1", 50.0);
		house->SetProfile( CityGeneration::TOSMProfile::FLAT_TERRACED);
		flatHouses.push_back(house);
	}

		{
		 CityGeneration::TInputProfile* house = new  CityGeneration::TInputProfile();
		{
			 CityGeneration::TContour* contour = new  CityGeneration::TContour();
			contour->type =  CityGeneration::TContourType::OUTER;
			contour->points.push_back(stingray::vector3(-200.0, -100.0,0.0));
			contour->points.push_back(stingray::vector3(-50.0, -100.0,0.0));
			contour->points.push_back(stingray::vector3(-50.0, -150.0,0.0));
			contour->points.push_back(stingray::vector3(50, -150,0.0));
			contour->points.push_back(stingray::vector3(50, -100.0,0.0));
			contour->points.push_back(stingray::vector3(200, -100.0,0.0));
			contour->points.push_back(stingray::vector3(200.0, 100.0,0.0));
			contour->points.push_back(stingray::vector3(-200.0, 100.0,0.0));
			house->AddContour(contour);
		}
		{
			 CityGeneration::TContour* contour = new  CityGeneration::TContour();
			contour->type =  CityGeneration::TContourType::INNER;
			contour->points.push_back(stingray::vector3(-150, -50.0,0.0));
			contour->points.push_back(stingray::vector3(-150, 50.0,0.0));
			contour->points.push_back(stingray::vector3(150, 50.0,0.0));
			contour->points.push_back(stingray::vector3(150, -50.0,0.0));
			house->AddContour(contour);
		}
		house->AddParameter("H", 100.0);
		house->AddParameter("ALPHA", PI/4.0);
		house->SetProfile( CityGeneration::TOSMProfile::HIPPED);
		flatHouses.push_back(house);
	}

	{
		 CityGeneration::TInputProfile* house = new  CityGeneration::TInputProfile();
		 CityGeneration::TContour* contour = new  CityGeneration::TContour();
		contour->type =  CityGeneration::TContourType::OUTER;
		contour->points.push_back(stingray::vector3(-200.0, -100.0,0.0));
		contour->points.push_back(stingray::vector3(-50.0, -100.0,0.0));
		contour->points.push_back(stingray::vector3(-50.0, -150.0,0.0));
		contour->points.push_back(stingray::vector3(50, -150,0.0));
		contour->points.push_back(stingray::vector3(50, -100.0,0.0));
		contour->points.push_back(stingray::vector3(200, -100.0,0.0));
		contour->points.push_back(stingray::vector3(200.0, 100.0,0.0));
		contour->points.push_back(stingray::vector3(-200.0, 100.0,0.0));
		house->AddContour(contour);
		house->AddParameter("H", 100.0);
		house->AddParameter("ALPHA", PI/4.0);
		house->SetProfile( CityGeneration::TOSMProfile::EQUAL_HIPPED);
		flatHouses.push_back(house);
	}

	{
		 CityGeneration::TInputProfile* house = new  CityGeneration::TInputProfile();
		 CityGeneration::TContour* contour = new  CityGeneration::TContour();
		contour->type =  CityGeneration::TContourType::OUTER;
		contour->points.push_back(stingray::vector3(0.0, 0.0,0.0));
		contour->points.push_back(stingray::vector3(-50.0, -20.0,0.0));
		contour->points.push_back(stingray::vector3(50, -100.0,0.0));
		contour->points.push_back(stingray::vector3(120.0, -60,0.0));
		contour->points.push_back(stingray::vector3(100.0, 0.0,0.0));
		house->AddContour(contour);
		house->AddParameter("H", 100.0);
		house->AddParameter("ALPHA", PI/4.0);
		house->SetProfile( CityGeneration::TOSMProfile::EQUAL_HIPPED);
		flatHouses.push_back(house);
	} 
	
	{
		 CityGeneration::TInputProfile* house = new  CityGeneration::TInputProfile();
		 CityGeneration::TContour* contour = new  CityGeneration::TContour();
		contour->type =  CityGeneration::TContourType::OUTER;
		contour->points.push_back(stingray::vector3(-200.0, -100.0,0.0));
		contour->points.push_back(stingray::vector3(200, -100.0,0.0));
		contour->points.push_back(stingray::vector3(200, 100,0.0));
		contour->points.push_back(stingray::vector3(220.0, 190.0,0.0));
		contour->points.push_back(stingray::vector3(150.0, 130.0,0.0));
		contour->points.push_back(stingray::vector3(-200.0, 100.0,0.0));
		house->AddContour(contour);
		house->AddParameter("H", 100.0);
		house->AddParameter("ALPHA", PI/4.0);
		house->SetProfile( CityGeneration::TOSMProfile::EQUAL_HIPPED);
		flatHouses.push_back(house);
	}
	
	{
		 CityGeneration::TInputProfile* house = new  CityGeneration::TInputProfile();
		{
			 CityGeneration::TContour* contour = new  CityGeneration::TContour();
			contour->type =  CityGeneration::TContourType::OUTER;
			contour->points.push_back(stingray::vector3(-200, -100.0,0.0));
			contour->points.push_back(stingray::vector3(200, -100.0,0.0));
			contour->points.push_back(stingray::vector3(200, 100.0,0.0));
			contour->points.push_back(stingray::vector3(-200, 100.0,0.0));
			house->AddContour(contour);
		}
		{
			 CityGeneration::TContour* contour = new  CityGeneration::TContour();
			contour->type =  CityGeneration::TContourType::INNER;
			contour->points.push_back(stingray::vector3(-150, -50.0,0.0));
			contour->points.push_back(stingray::vector3(-150, 50.0,0.0));
			contour->points.push_back(stingray::vector3(150, 50.0,0.0));
			contour->points.push_back(stingray::vector3(150, -50.0,0.0));
			house->AddContour(contour);
		}
		house->AddParameter("H", 100.0);
		house->AddParameter("ALPHA", PI/4.0);
		house->SetProfile( CityGeneration::TOSMProfile::EQUAL_HIPPED);
		flatHouses.push_back(house);
	}
	

    Donut::TSugarLoader::Instance().Init("data");   
	// Creating the rendering window
	Donut::TRenderer * window = new Donut::TRenderer();

	// Context info
	Donut::TContextDetail newContext;
	newContext.windowName = "roofGeneration";
	window->CreateRenderWindow(newContext, 1);
	window->SetVertexShader("shaders/canvas/ssaoV.glsl");
	window->SetFragmentShader("shaders/canvas/ssaoF.glsl");
	window->Init();

	// Getting the camera
	Donut::TRenderPass* pass= window->GetPasses()[0];
	pass->AddTexture("data/textures/random.bmp", "random");
	Donut::TNode* root= pass->GetRoot();
	Donut::Camera* camera = pass->GetCamera();
	Donut::TDefaultInputManager * inManager = new Donut::TDefaultInputManager();
	Donut::SetInputManager(inManager);
	inManager->FCamera = camera;
	camera->DefinePerspective(45.0,1280.0/720.0,0.1,5000.0);
	camera->Translate(Vector3(0.0, -200.0,-400.0));
	std::vector<Donut::TDrawableObject*> housesRenders;
	int counter = 0;
	for(auto houseIT = flatHouses.begin(); houseIT != flatHouses.end(); ++houseIT)
	{
		Donut::TDrawableObject* newHouse = GenerateDrawableMeshFromPoints(**houseIT);
		Donut::TSceneNode* node = new Donut::TSceneNode();
		node->Translate(TVec3(counter*300,0.0,-200.0));
		node->AddDrawable(newHouse);
		root->AddChild(node);
		window->RegisterToDraw(newHouse);
		housesRenders.push_back(newHouse);
		counter++;
	}

	
	while(window->IsRendering())
	{
		window->Draw();
		Donut::FarmEvents();
		inManager->Update(0.016);
		Sleep(16);
	}

	for(auto houseDrawer = housesRenders.begin(); houseDrawer != housesRenders.end(); ++houseDrawer)
	{
		window->UnRegisterToDraw(*houseDrawer);
		delete *houseDrawer;

	}
	delete window;
	return 0;

}
