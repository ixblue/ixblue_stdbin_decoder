#pragma once

#include "iXblue_stdbin_decoder/data_models/navigation_data/attitude_heading_deviation.h"
#include "iXblue_stdbin_decoder/memory_block_parser.h"

namespace StdBinDecoder
{
namespace Parser
{
class AttitudeHeadingDeviation : public MemoryBlockParser
{
public:
    AttitudeHeadingDeviation() : MemoryBlockParser(1, 12) {}
    void parse(boost::asio::mutable_buffer& buffer,
               Data::BinaryNav& outBinaryNav) override
    {
        Data::AttitudeHeadingDeviation res;
        buffer >> res.heading_stdDev_deg >> res.roll_stdDev_deg >> res.pitch_stdDev_deg;
        outBinaryNav.attitudeHeadingDeviation = res;
    }
};
} // namespace Parser
} // namespace StdBinDecoder
