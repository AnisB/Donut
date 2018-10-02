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
    #define PASS_NAME_TOKEN "name"
    #define PASS_TYPE_TOKEN "type"

    // CANVAS TOKENS
    #define CANVAS_NODE_TOKEN "canvas"
    #define CANVAS_DEPTH_TEST_ON_TOKEN "depth_test_on"
    #define CANVAS_DEPTH_TEST_OFF_TOKEN "depth_test_off"
    #define CANVAS_OUTPUTS_TOKEN "outputs"
    #define CANVAS_COLOR_OUTPUT_TOKEN "color"
    #define CANVAS_DEPTH_OUTPUT_TOKEN "depth"
    #define CANVAS_OUTPUT_NAME_TOKEN "name"

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

	void fill_canvas(rapidxml::xml_node<>* canvas, TPipelineCanvas& targetCanvas)
	{
		// The default behavior is the depth test being on (if nothing defined)
		rapidxml::xml_node<>* depth_test_on = canvas->first_node(CANVAS_DEPTH_TEST_ON_TOKEN);
		rapidxml::xml_node<>* depth_test_off = canvas->first_node(CANVAS_DEPTH_TEST_OFF_TOKEN);
		targetCanvas.depthTest = depth_test_on ? true : depth_test_off == nullptr;

		rapidxml::xml_node<>* outputs = canvas->first_node(CANVAS_OUTPUTS_TOKEN);
		if (outputs != nullptr)
		{
			for (rapidxml::xml_node<>* passNode = outputs->first_node(CANVAS_COLOR_OUTPUT_TOKEN); passNode; passNode = passNode->next_sibling(CANVAS_COLOR_OUTPUT_TOKEN))
			{
				uint32_t element_idx = targetCanvas.outputs.size();
				targetCanvas.outputs.resize(element_idx + 1);
				TCanvasOutput& output = targetCanvas.outputs[element_idx];
				output.slot = passNode->first_attribute(CANVAS_OUTPUT_NAME_TOKEN)->value();
				output.nature = TTextureNature::COLOR;
			}

			rapidxml::xml_node<>* depth_output = outputs->first_node(CANVAS_DEPTH_OUTPUT_TOKEN);
			if (depth_output)
			{
				uint32_t element_idx = targetCanvas.outputs.size();
				targetCanvas.outputs.resize(element_idx + 1);
				TCanvasOutput& output = targetCanvas.outputs[element_idx];
				output.slot = depth_output->first_attribute(CANVAS_OUTPUT_NAME_TOKEN)->value();
				output.nature = TTextureNature::DEPTH;
			}
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


        for(rapidxml::xml_node<>* passNode = pipeline_root->first_node(PASS_NODE_TOKEN); passNode; passNode = passNode->next_sibling(PASS_NODE_TOKEN))
        {
			uint32_t element_idx = _pipeline.passes.size();
			_pipeline.passes.resize(element_idx + 1);
            TPipelinePass& pass = _pipeline.passes[element_idx];

			// Grab the pass' type
			pass.tag = GetPassTag(passNode->first_attribute(PASS_TYPE_TOKEN)->value());

			// Grab the pass' name
			rapidxml::xml_attribute<>* pass_name = passNode->first_attribute(PASS_NAME_TOKEN);
			pass.name = pass_name ? pass_name->value() : "UNKNOWN";

			// Fill the canvas
			rapidxml::xml_node<>* canvas = passNode->first_node(CANVAS_NODE_TOKEN);
			if (canvas != nullptr)
			{
				fill_canvas(canvas, pass.canvas);
			}
            
            if (pass.tag == TPassTag::VFX)
            {
                // Filling the pass
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
            else if(pass.tag != TPassTag::GEOMETRY)
            {
                assert_fail_msg("Unkown pass type");
            }

        }
		return true;
	}
}