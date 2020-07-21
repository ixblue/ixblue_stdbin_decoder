#pragma once

#include "iXblue_stdbin_decoder/data_models/extended_navigation_data/vehicle_attitude_heading.h"
#include "iXblue_stdbin_decoder/data_serializer.h"

namespace StdBinDecoder
{
namespace Serializer
{
class VehicleAttitudeHeading : public DataSerializer
{
public:
    VehicleAttitudeHeading() : DataSerializer(3, 12) { }
    bool serialize(boost::asio::mutable_buffer& outBuffer,
                   const Data::BinaryNav& binaryNav) override
    {
        if (!binaryNav.vehicleAttitudeHeading.is_initialized()) {
            return false;
        }
        outBuffer << binaryNav.vehicleAttitudeHeading.get().heading_deg
                  << binaryNav.vehicleAttitudeHeading.get().roll_deg
                  << binaryNav.vehicleAttitudeHeading.get().pitch_deg;
        return true;
    }
};
} // namespace Serializer
} // namespace StdBinDecoder
