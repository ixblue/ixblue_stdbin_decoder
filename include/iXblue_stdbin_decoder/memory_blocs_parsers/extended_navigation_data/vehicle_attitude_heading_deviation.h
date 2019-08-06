#pragma once

#include "iXblue_stdbin_decoder/data_models/extended_navigation_data/vehicle_attitude_heading_deviation.h"
#include "iXblue_stdbin_decoder/memory_block_parser.h"

namespace StdBinDecoder
{
namespace Parser
{
class VehicleAttitudeHeadingDeviation : public MemoryBlockParser
{
public:
    VehicleAttitudeHeadingDeviation() : MemoryBlockParser(4, 12) {}
    void parse(boost::asio::mutable_buffer& buffer,
               Data::BinaryNav& outBinaryNav) override
    {
        Data::VehicleAttitudeHeadingDeviation res;
        buffer >> res.heading_stddev_deg >> res.roll_stddev_deg >> res.pitch_stddev_deg;
        outBinaryNav.vehicleAttitudeHeadingDeviation = res;
    }
};
} // namespace Parser
} // namespace StdBinDecoder