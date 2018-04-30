#pragma once

// Internal includes
#include "resource/pipeline_descriptor.h"

namespace donut
{
    bool read_pipeline(const char* _pipelineFileName, TPipelineDescriptor& _pipeline);
}