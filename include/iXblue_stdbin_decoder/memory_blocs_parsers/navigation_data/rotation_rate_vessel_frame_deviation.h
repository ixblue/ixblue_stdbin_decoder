#pragma once

#include "iXblue_stdbin_decoder/data_models/navigation_data/rotation_rate_vessel_frame_deviation.h"
#include "iXblue_stdbin_decoder/memory_block_parser.h"

namespace StdBinDecoder
{
namespace Parser
{
class RotationRateVesselFrameDeviation : public MemoryBlockParser
{
public:
    RotationRateVesselFrameDeviation() : MemoryBlockParser(30, 12) {}
    void parse(boost::asio::mutable_buffer& buffer,
               Data::BinaryNav& outBinaryNav) override
    {
        Data::RotationRateVesselFrameDeviation res;
        buffer >> res.xv1_stddev_degsec >> res.xv2_stddev_degsec >> res.xv3_stddev_degsec;
        outBinaryNav.rotationRateVesselFrameDeviation = res;
    }
};
} // namespace Parser
} // namespace StdBinDecoder