#ifndef FLOUR_DESCRIPTOR_H
#define FLOUR_DESCRIPTOR_H

// Library includes
#include "base/common.h"
#include "identifier.h"

// External includes
#include <vector>

namespace Donut
{
	// Environement descriptor
	struct TSHDescriptor
	{
		std::string red;
		std::string green;
		std::string blue;
	};

	struct TLightDescriptor
	{
		std::string pos;
		std::string diff;
		std::string spec;
		std::string ray;
	};

	struct TSkyboxDescriptor
	{
		std::string location;
		std::string extension;
	};

	struct TModelDescriptor
	{
		std::string sugarname;
	};
	
	struct TNodeDescriptor
	{
		TNodeDescriptor(bool _sceneNode = false)
		: tm("1 0 0 0 0 1 0 0 0 0 1 0 0 0 0 1")
		, skybox(nullptr)
		, nodes()
		, scenenode(_sceneNode)
		, models()
		{

		}

		bool scenenode;
		std::string tm;
		TSkyboxDescriptor* skybox;
		std::vector<TNodeDescriptor*> nodes;
		std::vector<std::string> models;
	};

	struct TIlluminationDescritor
	{
		std::vector<TLightDescriptor> lights;
	};

	// The descriptor
	struct TFlourDescriptor
	{
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

	void ParseFlourFile(const std::string& _fileName, TFlourDescriptor& _output);
}

#endif // FLOUR_DESCRIPTOR_H