// Library includes
#include "core/flour.h"
#include "core/scenenode.h"
#include "graphics/factory.h"
#include "core/sugarinstance.h"
#include "resource/resource_manager.h"
#include "butter/stream.h"
#include "base/stringhelper.h"
#include "resource/flour_descriptor.h"

namespace donut
{
	template<typename T>
	void stringConvertArray(const STRING_TYPE& _param, std::vector<T>& _values)
	{
		std::vector<STRING_TYPE> stringValues;
		split(_param, ' ', stringValues);
		for (const auto& val : stringValues)
		{
			_values.push_back(convert_from_string<T>(val));
		}
	}

	// Builda light from its descriptor
	void build_from_descriptor(const TLightDescriptor& light_descriptor, TLight& new_light)
	{
		new_light.SetPosition(light_descriptor.pos);
		new_light.SetDiffuse(light_descriptor.diff);
		new_light.SetSpecular(light_descriptor.spec);
		new_light.SetRay(light_descriptor.ray);
	}

	// Handle a spherical harmonic from its descriptor
	TSphericalHarmonics* HandleSphericalHarmonics(const TSHDescriptor& _SH)
	{
		TSphericalHarmonics* newSH = new TSphericalHarmonics();
		newSH->SetCoeffs(_SH.red, _SH.green, _SH.blue);
		return newSH;
	}

	/*
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
		node->SetTransformationMatrix(_node.tm);

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
	*/

	// Fetch a flour descriptor and build an instance of it
	TFlour* GenerateFlour(const STRING_TYPE& _flourName)
	{
		// Fetch the flour descriptor
		TFlourDescriptor _desc(*bento::common_allocator());

		// Create the runtime flour structure
		TFlour* flour = new TFlour(_flourName);

		// Fetch the rendering pipeline name
		flour->pipelineName = _desc.pipeline.c_str();

		// Handle the scene graph
		/*
		if (_desc.root)
		{
			flour->root = HandleNode(*_desc.root);
		}
		*/

		// Handle the lights
		const auto& lights_array = _desc.lights;
		uint32_t num_lights = (uint32_t)lights_array.size();
		flour->lights.resize(num_lights);
		for(uint32_t light_idx = 0; light_idx < num_lights; ++light_idx)
		{
			build_from_descriptor(lights_array[light_idx], flour->lights[light_idx]);
		}

		// If a skybox was defined, handle it
		if(_desc.skybox != "")
		{
			flour->skybox = ResourceManager::Instance().fetch_cubemap_id(_desc.skybox.c_str());
		}

		// If there is one, handle the sphericla harmonic env map
		if(_desc.sh.active)
		{
			flour->sh = HandleSphericalHarmonics(_desc.sh);
		}

		return flour;
	}
}