#ifndef FLOUR_DESCRIPTOR_H
#define FLOUR_DESCRIPTOR_H

// Library includes
#include "identifier.h"
#include "base/stringhelper.h"

// External includes
#include <vector>

namespace donut
{
	// Environement SH descriptor
	struct TSHDescriptor
	{
		STRING_TYPE red;
		STRING_TYPE green;
		STRING_TYPE blue;
	};

	// Light source descriptor
	struct TLightDescriptor
	{
		STRING_TYPE pos;
		STRING_TYPE diff;
		STRING_TYPE spec;
		STRING_TYPE ray;
	};

	// Skybox descriptor
	struct TSkyboxDescriptor
	{
		STRING_TYPE source;
	};

	// Sugar descriptor
	struct TModelDescriptor
	{
		STRING_TYPE sugarname;
	};
	
	// Node descriptor
	struct TNodeDescriptor
	{
		TNodeDescriptor(bool _sceneNode = false)
		: tm("1 0 0 0 0 1 0 0 0 0 1 0 0 0 0 1")
		, scenenode(_sceneNode)
        , nodes()
		, models()
		{

		}

		bool scenenode;
		STRING_TYPE tm;
		std::vector<TNodeDescriptor*> nodes;
		std::vector<STRING_TYPE> models;
	};

	// Illumination descriptor
	struct TIlluminationDescritor
	{
		std::vector<TLightDescriptor> lights;
	};

	// Flour descriptor
	struct TFlourDescriptor
	{
		TFlourDescriptor()
		: sh(nullptr)
		, skybox(nullptr)
		{

		}
		// Generic data
		STRING_TYPE name;
		STRING_TYPE file;

		// Rendering data
		STRING_TYPE pipeline;
		// Illumination data
		TSHDescriptor* sh;
		TSkyboxDescriptor* skybox;
		TIlluminationDescritor illumination;
		// Node Hierachy
		TNodeDescriptor* root;

        // For tracking the file's state
        RECIPE_GUID id;
	};

	// Build a descriptor from a file 
	void ParseFlourFile(const STRING_TYPE& _fileName, TFlourDescriptor& _output);
    bool HasChanged(const TFlourDescriptor& _flourDescriptor);
}

#endif // FLOUR_DESCRIPTOR_H