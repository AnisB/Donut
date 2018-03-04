// Library includes
#include "core/flour.h"
#include "butter/stream.h"
#include "core/scenenode.h"
#include "graphics/factory.h"
#include "core/sugarinstance.h"
#include "resource/flourloader.h"
#include "resource/resourcemanager.h"
#include "tools/fileloader.h"

namespace donut
{
	// Builda light from its descriptor
	void build_from_descriptor(const TLightDescriptor& light_descriptor, TLight& new_light)
	{
		new_light.SetPosition(convert_from_string<Vector3>(light_descriptor.pos));
		new_light.SetDiffuse(convert_from_string<Vector4>(light_descriptor.diff));
		new_light.SetSpecular(convert_from_string<Vector4>(light_descriptor.spec));
		new_light.SetRay(convert_from_string<float>(light_descriptor.ray));
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
	SKYBOX_GUID HandleSkyboxNode(const TSkyboxDescriptor& _skybox)
	{
		return ResourceManager::Instance().FetchSkybox(_skybox.location, _skybox.extension);
	}

	// Handle a node  from its descriptor
	TNode* HandleNode(const TNodeDescriptor& _node)
	{
		TNode* node = nullptr;
		
		// Instanciate the right noide type
		if(_node.scenenode)
		{
			node = new TSceneNode(*bento::common_allocator());
		}
		else
		{
			node = new TNode(*bento::common_allocator());
		}

		// Setting the matrix transform
		node->SetTransformationMatrix(convert_from_string<Matrix4>(_node.tm));

		// Setting its progeny
		for(auto& node_element : _node.nodes)
		{
			node->AttachChild(HandleNode(*node_element));
		}

		// If it is a scene node, make sure models are handled
		if(_node.scenenode)
		{
			// Downcast it to a scene node
			TSceneNode* sceneNode = static_cast<TSceneNode*>(node);
			for(const auto& sugar_name : _node.models)
			{
				TSugarInstance* sugar_instance = CreateSugarInstance(sugar_name);
				sceneNode->AppendDrawable(sugar_instance);
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
		const std::vector<TLightDescriptor>& light_descriptors = _desc.illumination.lights;
		uint32_t num_lights = light_descriptors.size();
		flour->lights.resize(num_lights);
		for(uint32_t light_idx = 0; light_idx < num_lights; ++light_idx)
		{
			build_from_descriptor(light_descriptors[light_idx], flour->lights[light_idx]);
		}

		// If a skybox was defined, handle it
		if(_desc.skybox)
		{
			flour->skybox = HandleSkyboxNode(*_desc.skybox);
		}

		// If there is one, handle the sphericla harmonic env map
		if(_desc.sh)
		{
			flour->sh = HandleSphericalHarmonics(*_desc.sh);
		}

		return flour;
	}
}