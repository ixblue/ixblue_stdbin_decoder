#pragma once

#include "iXblue_stdbin_decoder/data_models/navigation_data/smart_heave.h"
#include "iXblue_stdbin_decoder/memory_block_parser.h"

namespace ixblue_stdbin_decoder
{
namespace Parser
{
class SmartHeave : public MemoryBlockParser
{
public:
    SmartHeave() : MemoryBlockParser(3, 8) {}

    virtual void parse(boost::asio::mutable_buffer& buffer,
                       Data::BinaryNav& outBinaryNav) override
    {
        Data::SmartHeave res;
        buffer >> res.validityTime_100us >> res.smartHeave_m;
        outBinaryNav.smartHeave = res;
    }
};
} // namespace Parser
} // namespace ixblue_stdbin_decoder
