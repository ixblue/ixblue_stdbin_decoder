#pragma once

#include "iXblue_stdbin_decoder/data_models/navigation_data/speed_geographic_frame.h"
#include "iXblue_stdbin_decoder/memory_block_parser.h"

namespace StdBinDecoder
{
namespace Parser
{
class SpeedGeographicFrame : public MemoryBlockParser
{
public:
    SpeedGeographicFrame() : MemoryBlockParser(9, 12) {}
    void parse(boost::asio::mutable_buffer& buffer,
               Data::BinaryNav& outBinaryNav) override
    {
        Data::SpeedGeographicFrame res;
        buffer >> res.north_msec >> res.east_msec >> res.up_msec;
        outBinaryNav.speedGeographicFrame = res;
    }
};
} // namespace Parser
} // namespace StdBinDecoder