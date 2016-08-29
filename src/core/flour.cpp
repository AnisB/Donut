// Library includes
#include "flour.h"
#include "butter/stream.h"
#include "core/scenenode.h"
#include "graphics/factory.h"
#include "core/sugarinstance.h"
#include "resource/flourloader.h"
#include "tools/fileloader.h"

namespace Donut
{
	// Handle a light node from its descreiptor
	TLight* HandleLightNode(const TLightDescriptor& _lightDesc)
	{
		TLight* newLight = new TLight();
		newLight->SetPosition(convertFromString<Vector3>(_lightDesc.pos));
		newLight->SetDiffuse(convertFromString<Vector4>(_lightDesc.diff));
		newLight->SetSpecular(convertFromString<Vector4>(_lightDesc.spec));
		newLight->SetRay(convertFromString<float>(_lightDesc.ray));
		return newLight;
	}

	// Handle a spherical harmonic from its descriptor
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

	// Handle a skybox from its descriptor
	TSceneNode* HandleSkyboxNode(const TSkyboxDescriptor& _skybox)
	{
		TSceneNode* node = new TSceneNode();
		TMesh* mesh = CreateSkybox(_skybox.location, _skybox.extension);
		node->AddDrawable(mesh);
		return node;
	}

	// Handle a node  from its descriptor
	TNode* HandleNode(const TNodeDescriptor& _node)
	{
		TNode* node = nullptr;
		
		// Instanciate the right noide type
		if(_node.scenenode)
		{
			node = new TSceneNode();
		}
		else
		{
			node = new TNode();
		}

		// Setting the matrix transform
		node->SetTransformationMatrix(convertFromString<Matrix4>(_node.tm));

		// Setting its progeny
		foreach_macro(nodeIT, _node.nodes)
		{
			const TNodeDescriptor& currentNodeDescriptor = **nodeIT;
			node->AttachChild(HandleNode(currentNodeDescriptor));
		}

		// If a skybox was defined, handle it
		if(_node.skybox)
		{
			const TSkyboxDescriptor& skyboxDescriptor = *_node.skybox;
			node->AttachChild(HandleSkyboxNode(skyboxDescriptor));
		}

		// If it is a scene node, make sure models are handled
		if(_node.scenenode)
		{
			// Downcast it to a scene node
			TSceneNode* sceneNode = static_cast<TSceneNode*>(node);
			foreach_macro(sugarIT, _node.models)
			{
				const STRING_TYPE& sugarName = *sugarIT;
				TSugarInstance* sugarInstance = CreateSugarInstance(sugarName);
				sceneNode->AddDrawable(sugarInstance);
			}
		}

		// return the node
		return node;
	}


	// Fetch a flour descriptor and build an instance of it
	TFlour* GenerateFlour(const STRING_TYPE& _flourName)
	{
		// Fetch the flour descriptor
		const TFlourDescriptor& _desc = TFlourLoader::Instance().FetchFlour(_flourName);

		// Create the runtime flour structure
		TFlour* flour = new TFlour(_flourName);

		// Fetch the rendering pipeline name
		flour->pipelineName = _desc.pipeline;

		// Handle the scene graph
		if (_desc.root)
		{
			flour->root = HandleNode(*_desc.root);
		}

		// Handle the lights
		const std::vector<TLightDescriptor>& lights = _desc.illumination.lights;
		foreach_macro(light, lights)
		{
			const TLightDescriptor& currentLightDescriptor = *light;
			TLight* newLight = HandleLightNode(currentLightDescriptor);
			flour->lights.push_back(newLight);
		}


		// If there is one, handle the sphericla harmonic env map
		if(_desc.sh)
		{
			flour->sh = HandleSphericalHarmonics(*_desc.sh);
		}

		return flour;
	}
}