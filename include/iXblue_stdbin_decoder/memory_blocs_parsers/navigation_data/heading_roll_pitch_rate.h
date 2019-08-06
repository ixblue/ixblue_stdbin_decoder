#pragma once

#include "iXblue_stdbin_decoder/data_models/navigation_data/heading_roll_pitch_rate.h"
#include "iXblue_stdbin_decoder/memory_block_parser.h"

namespace StdBinDecoder
{
namespace Parser
{
class HeadingRollPitchRate : public MemoryBlockParser
{
public:
    HeadingRollPitchRate() : MemoryBlockParser(4, 12) {}
    void parse(boost::asio::mutable_buffer& buffer,
               Data::BinaryNav& outBinaryNav) override
    {
        Data::HeadingRollPitchRate res;
        buffer >> res.heading_rate >> res.roll_rate >> res.pitch_rate;
        outBinaryNav.headingRollPitchRate = res;
    }
};
} // namespace Parser
} // namespace StdBinDecoder