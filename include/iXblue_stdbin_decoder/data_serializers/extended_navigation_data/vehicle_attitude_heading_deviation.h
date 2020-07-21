#pragma once

#include "iXblue_stdbin_decoder/data_models/extended_navigation_data/vehicle_attitude_heading_deviation.h"
#include "iXblue_stdbin_decoder/data_serializer.h"

namespace StdBinDecoder
{
namespace Serializer
{
class VehicleAttitudeHeadingDeviation : public DataSerializer
{
public:
    VehicleAttitudeHeadingDeviation() : DataSerializer(4, 12) { }
    bool serialize(boost::asio::mutable_buffer& outBuffer,
                   const Data::BinaryNav& binaryNav) override
    {
        if (!binaryNav.vehicleAttitudeHeadingDeviation.is_initialized()) {
            return false;
        }
        outBuffer << binaryNav.vehicleAttitudeHeadingDeviation.get().heading_stddev_deg
                  << binaryNav.vehicleAttitudeHeadingDeviation.get().roll_stddev_deg
                  << binaryNav.vehicleAttitudeHeadingDeviation.get().pitch_stddev_deg;
        return true;
    }
};
} // namespace Serializer
} // namespace StdBinDecoder
