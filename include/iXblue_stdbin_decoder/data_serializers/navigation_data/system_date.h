#pragma once

#include "iXblue_stdbin_decoder/data_models/navigation_data/system_date.h"
#include "iXblue_stdbin_decoder/data_serializer.h"

namespace StdBinDecoder
{
namespace Serializer
{
class SystemDate : public DataSerializer
{
public:
    SystemDate() : DataSerializer(13, 4) { }
    bool serialize(boost::asio::mutable_buffer& outBuffer,
                   const Data::BinaryNav& binaryNav) override
    {
        if (!binaryNav.systemDate.is_initialized()) {
            return false;
        }
        outBuffer << binaryNav.systemDate.get().day
                  << binaryNav.systemDate.get().month
                  << binaryNav.systemDate.get().year;
        return true;
    }
};
} // namespace Serializer
} // namespace StdBinDecoder
