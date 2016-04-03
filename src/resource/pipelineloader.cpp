/**
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as
 * published by the Free Software Foundation, either version 3 of the
 * License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 *
 **/

// Library includes
#include "pipelineloader.h"
#include "base/common.h"
#include "tools/fileloader.h"
#include "tools/xmlhelpers.h"

#include "resourcemanager.h"
#include "resource/common.h"
#include "resource/shaderfilehandler.h"
#include "butter/types.h"
#include "butter/stream.h"
#include "rapidxml.hpp"

// STL includes
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <string.h>
#include <errno.h>
#include <fstream>

namespace Donut
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

    TPipelineLoader::TPipelineLoader()
    {

    }


    TPipelineLoader::~TPipelineLoader()
    {
        
    }

    void TPipelineLoader::Init()
    {
        RESOURCE_WARNING("========= PIPLINE LOADER INIT =========");
        LoadPipelines();
        RESOURCE_WARNING("=====================================");

    }

    void TPipelineLoader::LoadPipelines()
    {   
        const std::string& rootAssetDirectory = ResourceManager::Instance().RootAssetsFolder();
        std::string pipelineFolder(rootAssetDirectory + "/common/pipelines");

        std::vector<std::string> pipelineFiles;
        GetExtensionFileList(pipelineFolder, ".pipeline", pipelineFiles);
        foreach_macro(pipeline, pipelineFiles)
        {
            TPipelineDescriptor newPipeline;
            ParsePipelineFile(*pipeline, newPipeline);
            RESOURCE_INFO("Pipeline "<< newPipeline.name<<" file: "<< *pipeline);
            m_pipelines[newPipeline.name] = newPipeline;
        }
    }
   
    void TPipelineLoader::ParsePipelineFile(const std::string& _pipelineFileName, TPipelineDescriptor& _pipeline)
    {
        // reading the text file
        std::vector<char> buffer;
        ReadFile(_pipelineFileName.c_str(), buffer);

        // Parsing it
        rapidxml::xml_document<> doc;
        doc.parse<0>(&buffer[0]);

        // Fetching the root sugar node
        rapidxml::xml_node<>* pipeline_root = doc.first_node(PIPELINE_NODE_TOKEN);
        ASSERT_POINTER_NOT_NULL_NO_RELEASE(pipeline_root);

        // Fetching the pipeline's name
        _pipeline.name = pipeline_root->first_attribute(PIPELINE_NAME_TOKEN)->value();


        for(rapidxml::xml_node<>* passNode = pipeline_root->first_node(PASS_NODE_TOKEN); passNode; passNode = passNode->next_sibling())
        {
            TPipelinePass pass;
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
                    BuildShaderDescriptor(shader, pass.vfx.shader);
                }

                // textures node
                rapidxml::xml_node<>* textures = vfx->first_node(TEXTURES_NODE_TYPE_TOKEN);
                if(textures)
                {
                    BuildTexturesDescriptor(textures, pass.vfx.textures);
                }
            }
            else
            {
                ASSERT_FAIL_MSG("Unkown pass type");
            }
           


            // Append the step
            _pipeline.passes.push_back(pass);
        }
    }

    const TPipelineDescriptor& TPipelineLoader::FetchPipeline(const std::string& _pipelineName)
    {
        RESOURCE_DEBUG(_pipelineName<<" is requested");
        auto ite = m_pipelines.find(_pipelineName);
        ASSERT_MSG((ite!=m_pipelines.end()), "Pipeline not found: "<<_pipelineName);
        return ite->second;
    }

}