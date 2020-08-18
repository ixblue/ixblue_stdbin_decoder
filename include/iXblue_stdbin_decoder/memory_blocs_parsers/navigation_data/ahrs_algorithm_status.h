#pragma once

#include "iXblue_stdbin_decoder/data_models/navigation_data/ahrs_algorithm_status.h"
#include "iXblue_stdbin_decoder/memory_block_parser.h"

namespace ixblue_stdbin_decoder
{
namespace Parser
{
class AHRSAlgorithmStatus : public MemoryBlockParser
{
public:
    AHRSAlgorithmStatus() : MemoryBlockParser(18, 4) {}
    void parse(boost::asio::mutable_buffer& buffer,
               Data::BinaryNav& outBinaryNav) override
    {
        Data::AHRSAlgorithmStatus res;
        buffer >> res.status;
        outBinaryNav.ahrsAlgorithmStatus = res;
    }
};
} // namespace Parser
} // namespace ixblue_stdbin_decoder