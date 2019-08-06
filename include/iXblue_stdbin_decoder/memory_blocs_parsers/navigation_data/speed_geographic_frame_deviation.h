#pragma once

#include "iXblue_stdbin_decoder/data_models/navigation_data/speed_geographic_frame_deviation.h"
#include "iXblue_stdbin_decoder/memory_block_parser.h"

namespace StdBinDecoder
{
namespace Parser
{
class SpeedGeographicFrameDeviation : public MemoryBlockParser
{
public:
    SpeedGeographicFrameDeviation() : MemoryBlockParser(10, 12) {}
    void parse(boost::asio::mutable_buffer& buffer,
               Data::BinaryNav& outBinaryNav) override
    {
        Data::SpeedGeographicFrameDeviation res;
        buffer >> res.north_stddev_msec >> res.east_stddev_msec >> res.up_stddev_msec;
        outBinaryNav.speedGeographicFrameDeviation = res;
    }
};
} // namespace Parser
} // namespace StdBinDecoder