#pragma once

#include "iXblue_stdbin_decoder/data_models/navigation_data/ahrs_user_status.h"
#include "iXblue_stdbin_decoder/data_serializer.h"

namespace StdBinDecoder
{
namespace Serializer
{
class AHRSUserStatus : public DataSerializer
{
public:
    AHRSUserStatus() : DataSerializer(20, 4) { }
    bool serialize(boost::asio::mutable_buffer& outBuffer,
                   const Data::BinaryNav& binaryNav) override
    {
        if (!binaryNav.ahrsUserStatus.is_initialized()) {
            return false;
        }
        outBuffer << binaryNav.ahrsUserStatus.get().status;
        return true;
    }
};
} // namespace Serializer
} // namespace StdBinDecoder
