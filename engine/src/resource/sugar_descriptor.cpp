// Internal includes
#include "resource/sugar_descriptor.h"

// Bento includes
#include <bento_base/stream.h>

namespace bento
{
    uint32_t SUGAR_DESCRIPTOR_VERSION = 1;

    void pack_type(bento::Vector<char>& buffer, const donut::TRenderableDescriptor& sugar)
    {
        pack_type(buffer, sugar.id);
        pack_type(buffer, sugar.geometry);
        pack_type(buffer, sugar.material);
    }

    void unpack_type(const char*& stream, donut::TRenderableDescriptor& sugar)
    {
        unpack_type(stream, sugar.id);
        unpack_type(stream, sugar.geometry);
        unpack_type(stream, sugar.material);
    }

    void pack_type(bento::Vector<char>& buffer, const donut::TSugarDescriptor& sugar)
    {
        pack_bytes(buffer, SUGAR_DESCRIPTOR_VERSION);
        pack_type(buffer, sugar._name);
        pack_vector_types(buffer, sugar._renderables);
    }

    bool unpack_type(const char*& stream, donut::TSugarDescriptor& sugar)
    {
        // Read the version
        uint32_t data_stream_version;
        bento::unpack_bytes(stream, data_stream_version);

        // Stop if this does not match the current version
        if (data_stream_version != SUGAR_DESCRIPTOR_VERSION) return false;

        bento::unpack_type(stream, sugar._name);
        bento::unpack_vector_types(stream, sugar._renderables);
        return true;
    }
}