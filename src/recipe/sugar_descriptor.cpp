//Library include
#include "sugar_descriptor.h"
#include "tools/fileloader.h"
#include "tools/xmlhelpers.h"

// External includes
#include "rapidxml.hpp"

namespace donut
{
    // SUGAR DATA
    #define SUGAR_ROOT_TOKEN "sugar"
    #define SUGAR_NAME_TOKEN "name"

	// RENDERABLE DATA
	#define RENDERABLES_NODE_TOKEN "renderables"
	#define RENDERABLE_NODE_TOKEN "renderable"

    // GEOMETRY DATA
    #define GEOMETRY_ID_NODE_TOKEN "id"
    #define GEOMETRY_NODE_TOKEN "geometry"
    #define GEOMETRY_TYPE_TOKEN "type"
    #define GEOMETRY_LOCATION_TOKEN "location"

    // MATERIAL DATA
    #define MATERIAL_NODE_TOKEN "material"
    #define MATERIAL_NAME_TOKEN "name"

	void HandleRenderableArray(TSugarDescriptor& sugar_descriptor, rapidxml::xml_node<>* renderable_list_node)
	{
        // Count the number of renderables in the sugar
        uint32_t num_renderabes = 0;
		for (auto rend_node = renderable_list_node->first_node(RENDERABLE_NODE_TOKEN); rend_node; rend_node = rend_node->next_sibling(), ++num_renderabes)
		{
        }

        // Allocate the required memory
        sugar_descriptor._renderables.resize(num_renderabes);

        // Fill the allocated renderables
        uint32_t renderable_idx = 0;
        for (auto rend_node = renderable_list_node->first_node(RENDERABLE_NODE_TOKEN); rend_node; rend_node = rend_node->next_sibling(), ++renderable_idx)
        {
            // Fetch the renderable to fill
			TRenderableDescriptor& current_renderable = sugar_descriptor._renderables[renderable_idx];

            // Fetching the renderableID
            current_renderable._id = rend_node->first_attribute(GEOMETRY_ID_NODE_TOKEN)->value();

			// Fetching the geometry
			rapidxml::xml_node<>* geometry = rend_node->first_node(GEOMETRY_NODE_TOKEN);
			ASSERT_POINTER_NOT_NULL_NO_RELEASE(geometry);
			{
				current_renderable._geometry = geometry->first_attribute(GEOMETRY_LOCATION_TOKEN)->value();
			}

			// Fetching the data
			rapidxml::xml_node<>* material = rend_node->first_node(MATERIAL_NODE_TOKEN);
			ASSERT_POINTER_NOT_NULL_NO_RELEASE(material);
			{
				current_renderable._material = material->first_attribute(MATERIAL_NAME_TOKEN)->value();
			}
		}
	}

    void ParseSugarFile(const STRING_TYPE& _fileLocation, TSugarDescriptor& _sugar)
    {
        // reading the text file
        std::vector<char> buffer;
        ReadFile(_fileLocation.c_str(), buffer);

        // Set the file location
        _sugar._file = _fileLocation;

        // compute the GUID
        _sugar._id = GetFileHash(_fileLocation);

        // Parsing it
        rapidxml::xml_document<> doc;
        doc.parse<0>(&buffer[0]);

        // Fetching the root sugar node
        rapidxml::xml_node<>* sugar_root = doc.first_node(SUGAR_ROOT_TOKEN);
        ASSERT_POINTER_NOT_NULL_NO_RELEASE(sugar_root);

        // Fetching the name
        _sugar._name = sugar_root->first_attribute(SUGAR_NAME_TOKEN)->value();

		// Fetching the renderables
		rapidxml::xml_node<>* renderableArray = sugar_root->first_node(RENDERABLES_NODE_TOKEN);
		ASSERT_POINTER_NOT_NULL_NO_RELEASE(renderableArray);

		HandleRenderableArray(_sugar, renderableArray);
    }

    bool HasChanged(const TSugarDescriptor& _sugarDescriptor)
    {
        RECIPE_GUID id = GetFileHash(_sugarDescriptor._file);
        return id != _sugarDescriptor._id;
    }
}