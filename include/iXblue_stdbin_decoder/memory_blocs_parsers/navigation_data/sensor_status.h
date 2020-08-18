#pragma once

#include "iXblue_stdbin_decoder/data_models/navigation_data/sensor_status.h"
#include "iXblue_stdbin_decoder/memory_block_parser.h"

namespace ixblue_stdbin_decoder
{
namespace Parser
{
class SensorStatus : public MemoryBlockParser
{
public:
    SensorStatus() : MemoryBlockParser(14, 8) {}
    void parse(boost::asio::mutable_buffer& buffer,
               Data::BinaryNav& outBinaryNav) override
    {
        Data::SensorStatus res;
        buffer >> res.status1 >> res.status2;
        outBinaryNav.sensorStatus = res;
    }
};
} // namespace Parser
} // namespace ixblue_stdbin_decoder