//Library include
#include "sugardescriptor.h"
#include "tools/fileloader.h"
#include "tools/xmlhelpers.h"

// External includes
#include "rapidxml.hpp"

namespace Donut
{
    // SUGAR DATA
    #define SUGAR_ROOT_TOKEN "sugar"
    #define SUGAR_NAME_TOKEN "name"

	// RENDERABLE DATA
	#define RENDERABLES_NODE_TOKEN "renderables"
	#define RENDERABLE_NODE_TOKEN "renderable"

    // GEOMETRY DATA
    #define GEOMETRY_NODE_TOKEN "geometry"
    #define GEOMETRY_TYPE_TOKEN "type"
    #define GEOMETRY_LOCATION_TOKEN "location"

    // MATERIAL DATA
    #define MATERIAL_NODE_TOKEN "material"
    #define MATERIAL_NAME_TOKEN "name"

	void HandleRenderableArray(TSugarDescriptor& _descriptor, rapidxml::xml_node<>* _renderableListNodeNode)
	{
		for (rapidxml::xml_node<>* renderableNode = _renderableListNodeNode->first_node(RENDERABLE_NODE_TOKEN); renderableNode; renderableNode = renderableNode->next_sibling())
		{
			TRenderableDescriptor renderable;
			// Fetching the geometry
			rapidxml::xml_node<>* geometry = renderableNode->first_node(GEOMETRY_NODE_TOKEN);
			ASSERT_POINTER_NOT_NULL_NO_RELEASE(geometry);
			{
				renderable.geometry = geometry->first_attribute(GEOMETRY_LOCATION_TOKEN)->value();
			}

			// Fetching the data
			rapidxml::xml_node<>* material = renderableNode->first_node(MATERIAL_NODE_TOKEN);
			ASSERT_POINTER_NOT_NULL_NO_RELEASE(material);
			{
				renderable.material = material->first_attribute(MATERIAL_NAME_TOKEN)->value();
			}
			_descriptor.renderables.push_back(renderable);
		}
	}

    void ParseSugarFile(const STRING_TYPE& _fileLocation, TSugarDescriptor& _sugar)
    {
        // reading the text file
        std::vector<char> buffer;
        ReadFile(_fileLocation.c_str(), buffer);

        // Set the file location
        _sugar.file = _fileLocation;

        // compute the GUID
        _sugar.id = GetFileHash(_fileLocation);

        // Parsing it
        rapidxml::xml_document<> doc;
        doc.parse<0>(&buffer[0]);

        // Fetching the root sugar node
        rapidxml::xml_node<>* sugar_root = doc.first_node(SUGAR_ROOT_TOKEN);
        ASSERT_POINTER_NOT_NULL_NO_RELEASE(sugar_root);

        // Fetching the name
        _sugar.name = sugar_root->first_attribute(SUGAR_NAME_TOKEN)->value();

		// Fetching the renderables
		rapidxml::xml_node<>* renderableArray = sugar_root->first_node(RENDERABLES_NODE_TOKEN);
		ASSERT_POINTER_NOT_NULL_NO_RELEASE(renderableArray);

		HandleRenderableArray(_sugar, renderableArray);


    }

    bool HasChanged(const TSugarDescriptor& _sugarDescriptor)
    {
        RECIPE_GUID id = GetFileHash(_sugarDescriptor.file);
        return id != _sugarDescriptor.id;
    }
}