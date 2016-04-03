// Library includes
#include "flour.h"
#include "resource/flourloader.h"
#include "recipe/flourdescriptor.h"
#include "butter/stream.h"
#include "tools/fileloader.h"
#include "core/scenenode.h"
#include "graphics/factory.h"

namespace Donut
{

	TLight* HandleLightNode(const TLightDescriptor& _lightDesc)
	{
		TLight* newLight = new TLight();
		newLight->SetPosition(convertFromString<Vector3>(_lightDesc.pos));
		newLight->SetDiffuse(convertFromString<Vector4>(_lightDesc.diff));
		newLight->SetSpecular(convertFromString<Vector4>(_lightDesc.spec));
		newLight->SetRay(convertFromString<float>(_lightDesc.ray));
		return newLight;
	}

	TSphericalHarmonics* HandleSphericalHarmonics(const TSHDescriptor& _SH)
	{
		TSphericalHarmonics* newSH = new TSphericalHarmonics();
		std::vector<float> red, green, blue;
		stringConvertArray(_SH.red, red);
		stringConvertArray(_SH.green, green);
		stringConvertArray(_SH.blue, blue);
		newSH->SetCoeffs(red, green, blue);
		return newSH;
	}

	TSceneNode* HandleSkyboxNode(const TSkyboxDescriptor& _skybox)
	{
		TSceneNode* node = new TSceneNode();
		TMesh* mesh = CreateSkybox(_skybox.location, _skybox.extension);
		node->AddDrawable(mesh);
		return node;
	}

	TNode* HandleNode(const TNodeDescriptor& _node)
	{
		TNode* node = nullptr;
		if(_node.scenenode)
		{
			node = new TSceneNode();
		}
		else
		{
			node = new TNode();
		}
		// Setting the attributes
		node->SetTransformationMatrix(convertFromString<Matrix4>(_node.tm));

		foreach_macro(nodeIT, _node.nodes)
		{
			node->AttachChild(HandleNode(**nodeIT));
		}

		if(_node.skybox)
		{
			node->AttachChild(HandleSkyboxNode(*_node.skybox));
		}

		if(_node.scenenode)
		{
			TSceneNode* sceneNode = static_cast<TSceneNode*>(node);
			foreach_macro(sugarIT, _node.models)
			{
				TMesh* drwbl = CreateSugarInstance(*sugarIT);
				sceneNode->AddDrawable(drwbl);
			}
		}
		return node;
	}

	TFlour* GenerateFlour(const std::string& _flourName)
	{
		// Fetch the descriptor
		const TFlourDescriptor& _desc = TFlourLoader::Instance().FetchFlour(_flourName);

		// Create it
		TFlour* flour = new TFlour(_flourName);

		// Get the pipeline name
		flour->pipelineName = _desc.pipeline;

		const std::vector<TLightDescriptor>& lights = _desc.illumination.lights;

		foreach_macro(light, lights)
		{
			flour->lights.push_back(HandleLightNode(*light));
		}

		if(_desc.sh)
		{
			flour->sh = HandleSphericalHarmonics(*_desc.sh);
		}

		if(_desc.root)
		{
			flour->root = HandleNode(*_desc.root);
		}
		return flour;
	}
}