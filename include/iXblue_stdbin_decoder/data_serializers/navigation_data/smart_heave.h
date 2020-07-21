#pragma once

#include "iXblue_stdbin_decoder/data_models/navigation_data/smart_heave.h"
#include "iXblue_stdbin_decoder/data_serializer.h"

namespace StdBinDecoder
{
namespace Serializer
{
class SmartHeave : public DataSerializer
{
public:
    SmartHeave() : DataSerializer(3, 8) { }

    bool serialize(boost::asio::mutable_buffer& outBuffer,
                           const Data::BinaryNav& binaryNav) override
    {
        if (!binaryNav.smartHeave.is_initialized()) {
            return false;
        }
        outBuffer << binaryNav.smartHeave.get().validityTime_100us
                  << binaryNav.smartHeave.get().smartHeave_m;
        return true;
    }
};
} // namespace Serializer
} // namespace StdBinDecoder
