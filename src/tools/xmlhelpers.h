#ifndef DONUT_XML_PARSE_HELPER_H
#define DONUT_XML_PARSE_HELPER_H

// Library includes
#include "graphics/shader.h"
#include "graphics/shaderdata.h"
#include "rapidxml.hpp"

namespace Donut
{
	void BuildShaderDescriptor(rapidxml::xml_node<>* _shaderNode, TShader& _shader);
	void BuildTexturesDescriptor(rapidxml::xml_node<>* _texturesNode, std::vector<TTextureInfo>& _shader);
}

#endif // DONUT_XML_PARSE_HELPER_H