#ifndef TOPPING_DESCRIPTOR_H
#define TOPPING_DESCRIPTOR_H

// Library includes
#include "graphics/material.h"
#include "identifier.h"

// External includes
#include <vector>

namespace donut
{
	#define default_shader "INVALID"

	struct TShaderPipelineDescriptor
	{
		std::string	shaders[5];
		TShaderPipelineDescriptor()
		{
			for (uint32_t shad_idx = 0; shad_idx < 5; ++shad_idx)
			{
				shaders[shad_idx] = default_shader;
			}
		}
		TShaderPipelineDescriptor(const char* vertex, const char* fragment)
		{
			shaders[0] = vertex;
			shaders[4] = fragment;
			for (uint32_t shad_idx = 1; shad_idx < 4; ++shad_idx)
			{
				shaders[shad_idx] = default_shader;
			}
		}

		TShaderPipelineDescriptor(const char* vertex, const char* geometry, const char* fragment)
		{
			shaders[0] = vertex;
			shaders[3] = geometry;
			shaders[4] = fragment;
			for (uint32_t shad_idx = 1; shad_idx < 3; ++shad_idx)
			{
				shaders[shad_idx] = default_shader;
			}
		}
	};

	struct TShaderDataDescriptor
	{
		TShaderData::Type _type;
		std::string _slot;
		std::string _data;
	};

	// Topping descriptor
	struct TToppingDescriptor
	{
        STRING_TYPE								name;
        STRING_TYPE								file;
		TShaderPipelineDescriptor				shader_pipeline;
		std::vector<TShaderDataDescriptor>		data;

        // For tracking the file's state
        RECIPE_GUID id;
	};

	// Build a descriptor from a file 
	void ParseToppingFile(const char* _fileName, TToppingDescriptor& _output);
    bool HasChanged(const TToppingDescriptor& _toppingDescriptor);
}

#endif // TOPPING_DESCRIPTOR_H