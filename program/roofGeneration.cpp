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
		ASSERT_MSG((degree!= 3 || degree != 4), "one of the faces is a polygon");

		if (degree == 3)
		{
			for (auto ptsLoop =  currentFace.points.begin(); ptsLoop != currentFace.points.end(); ptsLoop++)
			{
				TLoop<stingray::Vector3>& loop = *ptsLoop;
				auto start = loop.GetFirstLoopable();
				auto it = start;
				do
				{

					positions.push_back(it->me.x);
					positions.push_back(it->me.y);
					positions.push_back(it->me.z);
					indexes.push_back(indexes.size());
					it = it->GetNext();
				} while(it != start);
			}
		}
		else if (degree ==4)
		{
			for (auto ptsLoop =  currentFace.points.begin(); ptsLoop != currentFace.points.end(); ptsLoop++)
			{
				TLoop<stingray::Vector3>& loop = *ptsLoop;
				auto start = loop.GetFirstLoopable();
				auto it1 = start->GetNext();
				auto it2 = it1->GetNext();
				auto it3 = it2->GetNext();

				positions.push_back(start->me.x);
				positions.push_back(start->me.y);
				positions.push_back(start->me.z);
				indexes.push_back(indexes.size());

				positions.push_back(it1->me.x);
				positions.push_back(it1->me.y);
				positions.push_back(it1->me.z);
				indexes.push_back(indexes.size());

				positions.push_back(it2->me.x);
				positions.push_back(it2->me.y);
				positions.push_back(it2->me.z);
				indexes.push_back(indexes.size());
				
				positions.push_back(start->me.x);
				positions.push_back(start->me.y);
				positions.push_back(start->me.z);
				indexes.push_back(indexes.size());

				positions.push_back(it2->me.x);
				positions.push_back(it2->me.y);
				positions.push_back(it2->me.z);
				indexes.push_back(indexes.size());

				positions.push_back(it3->me.x);
				positions.push_back(it3->me.y);
				positions.push_back(it3->me.z);
				indexes.push_back(indexes.size());
				
			}
		}
	}
	/*
	int nbPoints = _polygon.size();
	
	for (int i  = 0; i < nbPoints; ++i)
	{
		const stingray::Vector3& currentPoint = _polygon[i];
		const stingray::Vector3& nextPoint = _polygon[(i+1)%nbPoints];

		// Triangle 1
		positions.push_back(currentPoint.x);
		positions.push_back(currentPoint.y);
		positions.push_back(currentPoint.z);
		indexes.push_back(indexes.size());

		positions.push_back(nextPoint.x);
		positions.push_back(nextPoint.y);
		positions.push_back(nextPoint.z);
		indexes.push_back(indexes.size());

		positions.push_back(currentPoint.x );
		positions.push_back(currentPoint.y);
		positions.push_back(currentPoint.z- 100);
		indexes.push_back(indexes.size());

		// Triangle 2

		positions.push_back(currentPoint.x);
		positions.push_back(currentPoint.y);
		positions.push_back(currentPoint.z- 100);
		indexes.push_back(indexes.size());

		positions.push_back(nextPoint.x);
		positions.push_back(nextPoint.y);
		positions.push_back(nextPoint.z);
		indexes.push_back(indexes.size());

		positions.push_back(nextPoint.x);
		positions.push_back(nextPoint.y);
		positions.push_back(nextPoint.z-100);
		indexes.push_back(indexes.size());

	}
	*/
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

Donut::TDrawableObject* GenerateDrawableMeshFromPoints()
{
	std::vector<stingray::Vector3> points;
	points.push_back(stingray::vector3(0.0, 0.0,0.0));
	points.push_back(stingray::vector3(100.0, 0.0,0.0));
	points.push_back(stingray::vector3(0.0, 100.0,0.0));

	TOutput* output = generateRoof(points);

	Donut::TShader shader;
	shader.FVertexShader = "shaders/uniform/vertex.glsl";
	shader.FFragmentShader = "shaders/uniform/fragment.glsl";
	Donut::ShaderManager::Instance().CreateShader(shader);
	TModel* model = ComputeModel(output, shader, points);
	Donut::TMesh* hat = new Donut::TMesh(shader,model);
	return hat;
}

int main()
{
    Donut::TSugarLoader::Instance().Init("data");   
	// Creating the rendering window
	Donut::TRenderer * window = new Donut::TRenderer();

	// Context info
	Donut::TContextDetail newContext;
	newContext.windowName = "roofGeneration";
	window->CreateRenderWindow(newContext, 1);
	window->Init();

	// Getting the camera
	Donut::TRenderPass* pass= window->GetPasses()[0];
	Donut::TNode* root= pass->GetRoot();
	Donut::Camera* camera = pass->GetCamera();
	Donut::TDefaultInputManager * inManager = new Donut::TDefaultInputManager();
	Donut::SetInputManager(inManager);
	inManager->FCamera = camera;
	camera->DefinePerspective(45.0,1280.0/720.0,0.01,500.0);


	Donut::TDrawableObject* roof = GenerateDrawableMeshFromPoints();
	Donut::TSceneNode* node = new Donut::TSceneNode();
	node->AddDrawable(roof);
	root->AddChild(node);
	window->RegisterToDraw(roof);
	
	while(window->IsRendering())
	{
		window->Draw();
		Donut::FarmEvents();
		inManager->Update(0.016);
	}
	window->UnRegisterToDraw(roof);
	delete roof;
	delete window;
	return 0;

}
