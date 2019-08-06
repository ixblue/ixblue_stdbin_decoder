#pragma once

#include "iXblue_stdbin_decoder/data_models/navigation_data/system_date.h"
#include "iXblue_stdbin_decoder/memory_block_parser.h"

namespace StdBinDecoder
{
namespace Parser
{
class SystemDate : public MemoryBlockParser
{
public:
    SystemDate() : MemoryBlockParser(13, 4) {}
    void parse(boost::asio::mutable_buffer& buffer,
               Data::BinaryNav& outBinaryNav) override
    {
        Data::SystemDate res;
        buffer >> res.day >> res.month >> res.year;
        outBinaryNav.systemDate = res;
    }
};
} // namespace Parser
} // namespace StdBinDecoder