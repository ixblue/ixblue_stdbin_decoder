#pragma once

#include "iXblue_stdbin_decoder/data_models/external_data/utc.h"
#include "iXblue_stdbin_decoder/memory_block_parser.h"

namespace StdBinDecoder
{
namespace Parser
{
class Utc : public MemoryBlockParser
{
public:
    Utc() : MemoryBlockParser(0, 5) {}
    void parse(boost::asio::mutable_buffer& buffer,
               Data::BinaryNav& outBinaryNav) override
    {
        Data::Utc res;
        buffer >> res.validityTime_100us >> res.source;
        outBinaryNav.utc = res;
    }
};
} // namespace Parser
} // namespace StdBinDecoder