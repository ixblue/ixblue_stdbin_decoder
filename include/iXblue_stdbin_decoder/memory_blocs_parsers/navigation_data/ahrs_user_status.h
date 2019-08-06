#pragma once

#include "iXblue_stdbin_decoder/data_models/navigation_data/ahrs_user_status.h"
#include "iXblue_stdbin_decoder/memory_block_parser.h"

namespace StdBinDecoder
{
namespace Parser
{
class AHRSUserStatus : public MemoryBlockParser
{
public:
    AHRSUserStatus() : MemoryBlockParser(20, 4) {}
    void parse(boost::asio::mutable_buffer& buffer,
               Data::BinaryNav& outBinaryNav) override
    {
        Data::AHRSUserStatus res;
        buffer >> res.status;
        outBinaryNav.ahrsUserStatus = res;
    }
};
} // namespace Parser
} // namespace StdBinDecoder