#pragma once

#include "iXblue_stdbin_decoder/data_models/navigation_data/ins_algorithm_status.h"
#include "iXblue_stdbin_decoder/data_serializer.h"

namespace StdBinDecoder
{
namespace Serializer
{
class INSAlgorithmStatus : public DataSerializer
{
public:
    INSAlgorithmStatus() : DataSerializer(15, 16) { }
    bool serialize(boost::asio::mutable_buffer& outBuffer,
                   const Data::BinaryNav& binaryNav) override
    {
        if (!binaryNav.insAlgorithmStatus.is_initialized()) {
            return false;
        }
        outBuffer << binaryNav.insAlgorithmStatus.get().status1
                  << binaryNav.insAlgorithmStatus.get().status2
                  << binaryNav.insAlgorithmStatus.get().status3
                  << binaryNav.insAlgorithmStatus.get().status4;
        return true;
    }
};
} // namespace Serializer
} // namespace StdBinDecoder
