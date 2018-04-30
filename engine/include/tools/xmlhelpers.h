#pragma once

// Library includes
#include "graphics/shader.h"
#include "graphics/shaderdata.h"
#include "resource/topping_descriptor.h"
#include "rapidxml.hpp"

namespace donut
{
	// Build a shader from its xml node
	void BuildShaderPipelineDescriptor(rapidxml::xml_node<>* _shaderNode, TShaderPipelineDescriptor& shader);

	// Build uniform infos from a uniforms xml node
	void BuildUniformsDescriptor(rapidxml::xml_node<>* uniforms_nodes, std::vector<TShaderDataDescriptor>& topping_data);

	// Build texture infos from a textures xml node
	void BuildTexturesDescriptor(rapidxml::xml_node<>* _texturesNode, bento::Vector<TShaderDataDescriptor>& topping_data);
}