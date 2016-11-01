#ifndef FLOUR_DESCRIPTOR_H
#define FLOUR_DESCRIPTOR_H

// Library includes
#include "base/common.h"
#include "identifier.h"

// External includes
#include <vector>

namespace Donut
{
	// Environement SH descriptor
	struct TSHDescriptor
	{
		std::string red;
		std::string green;
		std::string blue;
	};

	// Light source descriptor
	struct TLightDescriptor
	{
		std::string pos;
		std::string diff;
		std::string spec;
		std::string ray;
	};

	// Skybox descriptor
	struct TSkyboxDescriptor
	{
		std::string location;
		std::string extension;
	};

	// Sugar descriptor
	struct TModelDescriptor
	{
		std::string sugarname;
	};
	
	// Node descriptor
	struct TNodeDescriptor
	{
		TNodeDescriptor(bool _sceneNode = false)
		: tm("1 0 0 0 0 1 0 0 0 0 1 0 0 0 0 1")
		, skybox(nullptr)
		, scenenode(_sceneNode)
        , nodes()
		, models()
		{

		}

		bool scenenode;
		std::string tm;
		TSkyboxDescriptor* skybox;
		std::vector<TNodeDescriptor*> nodes;
		std::vector<std::string> models;
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
		{

		}
		// Generic data
		std::string name;
		std::string file;

		// Rendering data
		std::string pipeline;
		TSHDescriptor* sh;
		TIlluminationDescritor illumination;
		TNodeDescriptor* root;

        // For tracking the file's state
        RECIPE_GUID id;
	};

	// Build a descriptor from a file 
	void ParseFlourFile(const std::string& _fileName, TFlourDescriptor& _output);
    bool HasChanged(const TFlourDescriptor& _flourDescriptor);
}

#endif // FLOUR_DESCRIPTOR_H