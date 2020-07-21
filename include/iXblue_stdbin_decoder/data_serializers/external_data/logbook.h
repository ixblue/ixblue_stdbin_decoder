#pragma once

#include "iXblue_stdbin_decoder/data_models/external_data/logbook.h"
#include "iXblue_stdbin_decoder/data_serializer.h"

namespace StdBinDecoder
{
namespace Serializer
{
class LogBook : public DataSerializer
{
public:
    LogBook() : DataSerializer(27, 12) { }
    bool serialize(boost::asio::mutable_buffer& outBuffer,
                   const Data::BinaryNav& binaryNav) override
    {
        if (!binaryNav.logBook.is_initialized()) {
            return false;
        }
        outBuffer << binaryNav.logBook.get().validityTime_100us
                  << binaryNav.logBook.get().log_id
                  << binaryNav.logBook.get().custom_text;
        return true;
    }
};
} // namespace Serializer
} // namespace StdBinDecoder
