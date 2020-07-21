#pragma once

#include "iXblue_stdbin_decoder/data_models/external_data/utc.h"
#include "iXblue_stdbin_decoder/data_serializer.h"

namespace StdBinDecoder
{
namespace Serializer
{
class Utc : public DataSerializer
{
public:
    Utc() : DataSerializer(0, 5) { }
    bool serialize(boost::asio::mutable_buffer& outBuffer,
                   const Data::BinaryNav& binaryNav) override
    {
        if (!binaryNav.utc.is_initialized()) {
            return false;
        }
        outBuffer << binaryNav.utc.get().validityTime_100us
                  << binaryNav.utc.get().source;
        return true;
    }
};
} // namespace Serializer
} // namespace StdBinDecoder
