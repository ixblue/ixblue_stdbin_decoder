#pragma once

#include "iXblue_stdbin_decoder/data_models/navigation_data/speed_vessel_frame.h"
#include "iXblue_stdbin_decoder/memory_block_parser.h"

namespace ixblue_stdbin_decoder
{
namespace Parser
{
class SpeedVesselFrame : public MemoryBlockParser
{
public:
    SpeedVesselFrame() : MemoryBlockParser(22, 12) {}
    void parse(boost::asio::mutable_buffer& buffer,
               Data::BinaryNav& outBinaryNav) override
    {
        Data::SpeedVesselFrame res;
        buffer >> res.xv1_msec >> res.xv2_msec >> res.xv3_msec;
        outBinaryNav.speedVesselFrame = res;
    }
};
} // namespace Parser
} // namespace ixblue_stdbin_decoder