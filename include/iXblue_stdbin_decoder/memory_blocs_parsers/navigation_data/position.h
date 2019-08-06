#pragma once

#include "iXblue_stdbin_decoder/data_models/navigation_data/position.h"
#include "iXblue_stdbin_decoder/memory_block_parser.h"

namespace StdBinDecoder
{
namespace Parser
{
class Position : public MemoryBlockParser
{
public:
    Position() : MemoryBlockParser(7, 21) {}
    void parse(boost::asio::mutable_buffer& buffer,
               Data::BinaryNav& outBinaryNav) override
    {
        Data::Position res;
        buffer >> res.latitude_deg >> res.longitude_deg >> res.altitude_ref >>
            res.altitude_m;
        outBinaryNav.position = res;
    }
};
} // namespace Parser
} // namespace StdBinDecoder