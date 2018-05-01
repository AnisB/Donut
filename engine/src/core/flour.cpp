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

	// Handle a node  from its descriptor
	void build_hierarchy(TFlour& target_flour, const TFlourDescriptor& floor_descriptor)
	{
		uint32_t num_nodes = floor_descriptor.nodes.size();
		target_flour.nodes.resize(num_nodes);

		for (uint32_t node_idx = 0; node_idx < num_nodes; ++node_idx)
		{
			TNode& current_node = target_flour.nodes[node_idx];
			const TNodeDescriptor& source_node = floor_descriptor.nodes[node_idx];
			current_node.SetTransformationMatrix(source_node.tm);
			for (const auto& sugar_name : source_node.models)
			{
				TSugarInstance* sugar_instance = CreateSugarInstance(sugar_name.c_str());
				current_node.AppendDrawable(sugar_instance);
			}
			for (const auto& child_idx : source_node.children)
			{
				current_node.AttachChild(&target_flour.nodes[child_idx]);
			}
		}
	}

	// Fetch a flour descriptor and build an instance of it
	TFlour* GenerateFlour(const char* flour_name)
	{
		// Fetch the flour descriptor
		TFlourDescriptor flour_desc(*bento::common_allocator());
		bool request_res = ResourceManager::Instance().request_asset<TFlourDescriptor>(flour_name, flour_desc);
		if (!request_res) return nullptr;

		// Create the runtime flour structure
		TFlour* flour = new TFlour(*bento::common_allocator());

		// Fetch the rendering pipeline name
		flour->pipelineName = flour_desc.pipeline.c_str();

		// Handle the scene graph
		build_hierarchy(*flour, flour_desc);

		// Handle the lights
		const auto& lights_array = flour_desc.lights;
		uint32_t num_lights = (uint32_t)lights_array.size();
		flour->lights.resize(num_lights);
		for(uint32_t light_idx = 0; light_idx < num_lights; ++light_idx)
		{
			build_from_descriptor(lights_array[light_idx], flour->lights[light_idx]);
		}

		// If a skybox was defined, handle it
		if(flour_desc.skybox != "")
		{
			flour->skybox = ResourceManager::Instance().fetch_cubemap_id(flour_desc.skybox.c_str());
		}

		// If there is one, handle the sphericla harmonic env map
		if(flour_desc.sh.active)
		{
			flour->sh = HandleSphericalHarmonics(flour_desc.sh);
		}

		return flour;
	}
}