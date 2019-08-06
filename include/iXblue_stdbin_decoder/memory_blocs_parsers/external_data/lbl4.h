#pragma once

#include "iXblue_stdbin_decoder/data_models/external_data/lbl.h"
#include "iXblue_stdbin_decoder/memory_block_parser.h"

namespace StdBinDecoder
{
namespace Parser
{
class Lbl4 : public MemoryBlockParser
{
public:
    Lbl4() : MemoryBlockParser(17, 41) {}
    void parse(boost::asio::mutable_buffer& buffer,
               Data::BinaryNav& outBinaryNav) override
    {
        Data::Lbl res;
        buffer >> res.validityTime_100us >> res.rfu >> res.beacon_id >>
            res.beacon_latitude_deg >> res.beacon_longitude_deg >>
            res.beacon_altitude_m >> res.range_m >> res.range_stddev_m;
        outBinaryNav.lbl4 = res;
    }
};
} // namespace Parser
} // namespace StdBinDecoder