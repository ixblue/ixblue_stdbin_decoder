#pragma once

#include "iXblue_stdbin_decoder/data_models/external_data/dmi.h"
#include "iXblue_stdbin_decoder/data_serializer.h"

namespace StdBinDecoder
{
namespace Serializer
{
class Dmi : public DataSerializer
{
public:
    Dmi() : DataSerializer(13, 8) { }
    bool serialize(boost::asio::mutable_buffer& outBuffer,
                   const Data::BinaryNav& binaryNav) override
    {
        if (!binaryNav.dmi.is_initialized()) {
            return false;
        }
        outBuffer << binaryNav.dmi.get().validityTime_100us
                  << binaryNav.dmi.get().pulse_count;
        return true;
    }
};
} // namespace Serializer
} // namespace StdBinDecoder
