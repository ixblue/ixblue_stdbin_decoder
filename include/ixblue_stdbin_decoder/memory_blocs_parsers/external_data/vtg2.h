#pragma once

#include "ixblue_stdbin_decoder/data_models/external_data/vtg.h"
#include "ixblue_stdbin_decoder/memory_block_parser.h"

namespace ixblue_stdbin_decoder
{
namespace Parser
{
class Vtg2 : public MemoryBlockParser
{
public:
    Vtg2() : MemoryBlockParser(26, 17) {}
    void parse(boost::asio::const_buffer& buffer,
               Data::BinaryNav& outBinaryNav) override
    {
        Data::Vtg res;
        buffer >> res.validityTime_100us >> res.vtg_id >> res.true_course_deg >>
            res.magnetic_course_deg >> res.speed_over_ground_ms;
        outBinaryNav.vtg2 = res;
    }
};
} // namespace Parser
} // namespace ixblue_stdbin_decoder