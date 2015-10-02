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

TModel* ComputeModel(TOutput* _output,const Donut::TShader& parShader, const std::vector<stingray::Vector3>& _polygon)
{
	TModel* newModel = new TModel();
	std::vector<float> positions;
	std::vector<unsigned int> indexes;

	auto faces = _output->faces;
	for (auto f =  faces.begin(); f != faces.end(); f++)
	{
		TOutput::TFace& currentFace = *f->second;
		int degree =  currentFace.pointCount();
		//ASSERT_MSG(degree >= 3, "one of the faces is a polygon");

		if (degree>=3)
		{
			for (auto ptsLoop =  currentFace.points.begin(); ptsLoop != currentFace.points.end(); ptsLoop++)
			{
				TLoop<stingray::Vector3>& loop = *ptsLoop;
				auto start = loop.GetFirstLoopable();
				auto it1 = start->GetNext();
				auto it2 = it1->GetNext();
				do
				{
					positions.push_back(start->me.y);
					positions.push_back(start->me.z);
					positions.push_back(start->me.x);
					indexes.push_back(indexes.size());

					positions.push_back(it1->me.y);
					positions.push_back(it1->me.z);
					positions.push_back(it1->me.x);
					indexes.push_back(indexes.size());

					positions.push_back(it2->me.y);
					positions.push_back(it2->me.z);
					positions.push_back(it2->me.x);
					indexes.push_back(indexes.size());

					it1 = it2;
					it2 = it2->GetNext();
				} while(it2 != start);
			}
		}
	}
	
	int nbPoints = _polygon.size();
	
	for (int i  = 0; i < nbPoints; ++i)
	{
		const stingray::Vector3& currentPoint = _polygon[i];
		const stingray::Vector3& nextPoint = _polygon[(i+1)%nbPoints];

		// Triangle 1
		positions.push_back(currentPoint.y);
		positions.push_back(currentPoint.z);
		positions.push_back(currentPoint.x);
		indexes.push_back(indexes.size());

		positions.push_back(currentPoint.y);
		positions.push_back(currentPoint.z -100);
		positions.push_back(currentPoint.x);
		indexes.push_back(indexes.size());

		positions.push_back(nextPoint.y);
		positions.push_back(nextPoint.z);
		positions.push_back(nextPoint.x);
		indexes.push_back(indexes.size());

		// Triangle 2

		positions.push_back(currentPoint.y);
		positions.push_back(currentPoint.z - 100);
		positions.push_back(currentPoint.x);
		indexes.push_back(indexes.size());


		positions.push_back(nextPoint.y);
		positions.push_back(nextPoint.z-100);
		positions.push_back(nextPoint.x);
		indexes.push_back(indexes.size());

		positions.push_back(nextPoint.y);
		positions.push_back(nextPoint.z);
		positions.push_back(nextPoint.x);
		indexes.push_back(indexes.size());


	}
	
	std::vector<float> data = positions;
	
	for(int i  = 0; i < positions.size(); i+=9)
	{
		Vector3 p0 (positions[i], positions[i+1], positions[i+2]);
		Vector3 p1(positions[i+3], positions[i+4], positions[i+5]);
		Vector3 p2(positions[i+6], positions[i+7], positions[i+8]);
		Vector3 normal = (Vector3::crossProduct(p1-p0, p2-p0));
		normal = normal/normal.Norm();
		for (int j =0; j <3 ; ++j)
		{
			GENERAL_DEBUG(normal.x<<" "<<normal.y<<" "<<normal.z);
			data.push_back(-normal.x/2.0 +0.5);
			data.push_back(-normal.y/2.0 +0.5);
			data.push_back(-normal.z/2.0 +0.5);
		}
	}
	
	GLuint VAO;
	glGenVertexArrays (1, &VAO);
	glBindVertexArray (VAO);
	GLuint VBO;
	GLuint IBO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GL_FLOAT)*data.size(), &data[0], GL_STATIC_DRAW);

	glGenBuffers(1, &IBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int)*indexes.size(), &indexes[0], GL_STATIC_DRAW);

	GLuint posAtt = glGetAttribLocation(parShader.FProgramID, "position");
	GLuint normalAtt = glGetAttribLocation(parShader.FProgramID, "normal");

	glEnableVertexAttribArray (posAtt);
	glEnableVertexAttribArray (normalAtt);

	glVertexAttribPointer (posAtt, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glVertexAttribPointer (normalAtt, 3, GL_FLOAT, GL_FALSE, 0, (void*)(sizeof (GLfloat)*indexes.size()*3));

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	newModel->vertexArray = VAO;
	newModel->nbVertices = indexes.size();

	return newModel;
}

Donut::TDrawableObject* GenerateDrawableMeshFromPoints(const std::vector<stingray::Vector3>& _points)
{
	TOutput* output = generateRoof(_points);

	Donut::TShader shader;
	shader.FVertexShader = "shaders/uniform/vertex.glsl";
	shader.FFragmentShader = "shaders/uniform/fragment.glsl";
	Donut::ShaderManager::Instance().CreateShader(shader);
	TModel* model = ComputeModel(output, shader, _points);
	Donut::TMesh* hat = new Donut::TMesh(shader,model);
	return hat;
}


int main()
{

	std::vector<std::vector<stingray::Vector3>> houses;
	
	{
		std::vector<stingray::Vector3> house;
		house.push_back(stingray::vector3(-200.0, -100.0,0.0));
		house.push_back(stingray::vector3(-50.0, -100.0,0.0));
		house.push_back(stingray::vector3(-50.0, -150.0,0.0));
		house.push_back(stingray::vector3(50, -150,0.0));
		house.push_back(stingray::vector3(50, -100.0,0.0));
		house.push_back(stingray::vector3(200, -100.0,0.0));
		house.push_back(stingray::vector3(200.0, 100.0,0.0));
		house.push_back(stingray::vector3(-200.0, 100.0,0.0));
		houses.push_back(house);
	}

		
	{
		std::vector<stingray::Vector3> house;
		house.push_back(stingray::vector3(0.0, 0.0,0.0));
		house.push_back(stingray::vector3(-50.0, -20.0,0.0));
		house.push_back(stingray::vector3(50, -100.0,0.0));
		house.push_back(stingray::vector3(120.0, -60,0.0));
		house.push_back(stingray::vector3(100.0, 0.0,0.0));
		houses.push_back(house);
	} 
	
	{
		std::vector<stingray::Vector3> house;
		house.push_back(stingray::vector3(-200.0, -100.0,0.0));
		house.push_back(stingray::vector3(200, -100.0,0.0));
		house.push_back(stingray::vector3(200.0, 170.0,0.0));
		house.push_back(stingray::vector3(150.0, 130.0,0.0));
		house.push_back(stingray::vector3(-200.0, 100.0,0.0));
		houses.push_back(house);
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

	std::vector<Donut::TDrawableObject*> housesRenders;
	int counter = 0;
	for(auto houseIT = houses.begin(); houseIT != houses.end(); ++houseIT)
	{
		Donut::TDrawableObject* newHouse = GenerateDrawableMeshFromPoints(*houseIT);
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
	}

	for(auto houseDrawer = housesRenders.begin(); houseDrawer != housesRenders.end(); ++houseDrawer)
	{
		window->UnRegisterToDraw(*houseDrawer);
		delete *houseDrawer;

	}
	delete window;
	return 0;

}
