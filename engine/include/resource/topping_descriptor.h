#pragma once

// bento includes
#include <bento_collection/dynamic_string.h>
#include <bento_collection/vector.h>

// Internal include
#include "resource/topping_descriptor.h"
#include "graphics/shaderdata.h"

namespace donut
{
	#define default_shader "INVALID"

	struct TShaderPipelineDescriptor
	{
		ALLOCATOR_BASED;

		bento::DynamicString vertex;
		bento::DynamicString tess_control;
		bento::DynamicString tess_eval;
		bento::DynamicString geometry;
		bento::DynamicString fragment;

		TShaderPipelineDescriptor(bento::IAllocator& alloc)
		: vertex(alloc)
		, tess_control(alloc)
		, tess_eval(alloc)
		, geometry(alloc)
		, fragment(alloc)
		{
			vertex = default_shader;
			tess_control = default_shader;
			tess_eval = default_shader;
			geometry = default_shader;
			fragment = default_shader;
		}

		TShaderPipelineDescriptor(bento::IAllocator& alloc, const char* vertex_path, const char* fragment_path)
		: vertex(alloc)
		, tess_control(alloc)
		, tess_eval(alloc)
		, geometry(alloc)
		, fragment(alloc)		
		{
			vertex = vertex_path;
			tess_control = default_shader;
			tess_eval = default_shader;
			geometry = default_shader;
			fragment = fragment_path;
		}

		TShaderPipelineDescriptor(bento::IAllocator& alloc, const char* vertex_path, const char* geometry_path, const char* fragment_path)
		: vertex(alloc)
		, tess_control(alloc)
		, tess_eval(alloc)
		, geometry(alloc)
		, fragment(alloc)		
		{
			vertex = vertex_path;
			tess_control = default_shader;
			tess_eval = default_shader;
			geometry = geometry_path;
			fragment = fragment_path;
		}
	};

	struct TShaderDataDescriptor
	{
		ALLOCATOR_BASED;
		TShaderDataDescriptor(bento::IAllocator& alloc)
		: type((uint8_t)TShaderDataType::TYPE)
		, slot(alloc)
		, data(alloc)
		{

		}
		uint8_t type;
		bento::DynamicString slot;
		bento::DynamicString data;
	};

	struct TToppingDescriptor
	{
		ALLOCATOR_BASED;
		TToppingDescriptor(bento::IAllocator& alloc)
		: name(alloc)
		, shader_pipeline(alloc)
		, data(alloc)
		{
		}
        bento::DynamicString					name;
		TShaderPipelineDescriptor				shader_pipeline;
		bento::Vector<TShaderDataDescriptor>	data;
	};
}

namespace bento
{
	void pack_type(bento::Vector<char>& buffer, const donut::TShaderDataDescriptor& shader_data);
	void unpack_type(const char*& stream, donut::TShaderDataDescriptor& shader_data);

	void pack_type(bento::Vector<char>& buffer, const donut::TShaderPipelineDescriptor& shader_pipeline);
	void unpack_type(const char*& stream, donut::TShaderPipelineDescriptor& shader_pipeline);

	void pack_type(bento::Vector<char>& buffer, const donut::TToppingDescriptor& topping);
	bool unpack_type(const char*& stream, donut::TToppingDescriptor& topping);
}