#pragma once

#include "iXblue_stdbin_decoder/data_models/navigation_data/sensor_status.h"
#include "iXblue_stdbin_decoder/data_serializer.h"

namespace StdBinDecoder
{
namespace Serializer
{
class SensorStatus : public DataSerializer
{
public:
    SensorStatus() : DataSerializer(14, 8) { }
    bool serialize(boost::asio::mutable_buffer& outBuffer,
                   const Data::BinaryNav& binaryNav) override
    {
        if (!binaryNav.sensorStatus.is_initialized()) {
            return false;
        }
        outBuffer << binaryNav.sensorStatus.get().status1
                  << binaryNav.sensorStatus.get().status2;
        return true;
    }
};
} // namespace Serializer
} // namespace StdBinDecoder
