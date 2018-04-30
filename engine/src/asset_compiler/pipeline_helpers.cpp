// Internal includes
#include "asset_compiler/pipeline_helpers.h"

// Bento includes
#include <bento_base/security.h>
#include <bento_tools/file_system.h>

// Library include
#include "resource/pipeline_descriptor.h"
#include "tools/xmlhelpers.h"

// External includes
#include "rapidxml.hpp"

namespace donut
{
	// PIPELINE TOKENS
    #define PIPELINE_NODE_TOKEN "pipeline"
    #define PIPELINE_NAME_TOKEN "name"

    // STEP TOKENS
    #define PASS_NODE_TOKEN "pass"
    #define PASS_TYPE_TOKEN "type"

    // CANVAS TOKENS
    #define CANVAS_NODE_TOKEN "canvas"
    #define CANVAS_TYPE_TOKEN "type"
    #define CANVAS_OUTPUT_TOKEN "output"

    // PASS TOKENS
    #define VFX_NODE_TOKEN "vfx"
    #define VFX_TYPE_TOKEN "type"
    #define SHADER_NODE_TYPE_TOKEN "shader"
    #define TEXTURES_NODE_TYPE_TOKEN "textures"

    TVFXTag::Type GetVFXTag(const std::string& _tag)
    {
        if(_tag == "simplefx")
        {
            return TVFXTag::SIMPLEFX;
        }
        else if(_tag == "deffered")
        {
            return TVFXTag::DEFFERED;
        }
        else if(_tag == "environement")
        {
            return TVFXTag::ENVIRONEMENT;
        }
        else if(_tag == "skybox")
        {
            return TVFXTag::SKYBOX;
        }
        else
        {
            return TVFXTag::UNKNOWN;
        } 
    }

    TCanvasTag::Type GetCanvasTag(const std::string& _tag)
    {
        if(_tag == "empty")
        {
            return TCanvasTag::EMPTY;
        }
        else if(_tag == "effect")
        {
            return TCanvasTag::EFFECT;

        }
        else if(_tag == "gbuffer")
        {
            return TCanvasTag::GBUFFER;
        }
        else
        {
            return TCanvasTag::UNKNOWN;
        } 
    }

    TPassTag::Type GetPassTag(const std::string& _tag)
    {
        if(_tag == "geometry")
        {
            return TPassTag::GEOMETRY;
        }
        else if(_tag == "vfx")
        {
            return TPassTag::VFX;
        }
        else
        {
            return TPassTag::UNKNOWN;
        } 
    }

    bool read_pipeline(const char* _pipelineFileName, TPipelineDescriptor& _pipeline)
    {
        // reading the text file
        bento::Vector<char> buffer(*bento::common_allocator());
		bento::read_file(_pipelineFileName, buffer, bento::FileType::Text);

        // Parsing it
        rapidxml::xml_document<> doc;
        doc.parse<0>(&buffer[0]);

        // Fetching the root sugar node
        rapidxml::xml_node<>* pipeline_root = doc.first_node(PIPELINE_NODE_TOKEN);
        assert(pipeline_root);

        // Fetching the pipeline's name
        _pipeline.name = pipeline_root->first_attribute(PIPELINE_NAME_TOKEN)->value();


        for(rapidxml::xml_node<>* passNode = pipeline_root->first_node(PASS_NODE_TOKEN); passNode; passNode = passNode->next_sibling())
        {
			uint32_t element_idx = _pipeline.passes.size();
			_pipeline.passes.resize(element_idx + 1);
            TPipelinePass& pass = _pipeline.passes[element_idx];
            
			pass.tag = GetPassTag(passNode->first_attribute(PASS_TYPE_TOKEN)->value());
            if(pass.tag == TPassTag::GEOMETRY)
            {
                // Fetch the canvas
                rapidxml::xml_node<>* canvas = passNode->first_node(CANVAS_NODE_TOKEN);
                 // Filling the canvas
                pass.canvas.tag = GetCanvasTag(canvas->first_attribute(CANVAS_TYPE_TOKEN)->value());
                rapidxml::xml_attribute<>* canvasOutput = canvas->first_attribute(CANVAS_OUTPUT_TOKEN);
                if(canvasOutput)
                {
                    pass.canvas.output = canvas->first_attribute(CANVAS_OUTPUT_TOKEN)->value();
                }
            }
            else if (pass.tag == TPassTag::VFX)
            {
                // Fetch the canvas
                rapidxml::xml_node<>* canvas = passNode->first_node(CANVAS_NODE_TOKEN);

                // Filling the canvas
                pass.canvas.tag = GetCanvasTag(canvas->first_attribute(CANVAS_TYPE_TOKEN)->value());
                rapidxml::xml_attribute<>* canvasOutput = canvas->first_attribute(CANVAS_OUTPUT_TOKEN);
                if(canvasOutput)
                {
                    pass.canvas.output = canvas->first_attribute(CANVAS_OUTPUT_TOKEN)->value();
                }

                // Fillinf the pass
                rapidxml::xml_node<>* vfx = passNode->first_node(VFX_NODE_TOKEN);
                pass.vfx.tag = GetVFXTag(vfx->first_attribute(VFX_TYPE_TOKEN)->value());

                // shader node
                rapidxml::xml_node<>* shader = vfx->first_node(SHADER_NODE_TYPE_TOKEN);
                if(shader)
                {
					BuildShaderPipelineDescriptor(shader, pass.vfx.shader_pipeline);
                }

                // textures node
                rapidxml::xml_node<>* textures = vfx->first_node(TEXTURES_NODE_TYPE_TOKEN);
                if(textures)
                {
					BuildTexturesDescriptor(textures, pass.vfx.data);
                }
            }
            else
            {
                assert_fail_msg("Unkown pass type");
            }

        }
		return true;
	}
}