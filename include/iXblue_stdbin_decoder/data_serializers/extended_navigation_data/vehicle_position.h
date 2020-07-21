#pragma once

#include "iXblue_stdbin_decoder/data_models/extended_navigation_data/vehicle_position.h"
#include "iXblue_stdbin_decoder/data_serializer.h"

namespace StdBinDecoder
{
namespace Serializer
{
class VehiclePosition : public DataSerializer
{
public:
    VehiclePosition() : DataSerializer(5, 21) { }
    bool serialize(boost::asio::mutable_buffer& outBuffer,
                   const Data::BinaryNav& binaryNav) override
    {
        if (!binaryNav.vehiclePosition.is_initialized()) {
            return false;
        }
        outBuffer << binaryNav.vehiclePosition.get().latitude_deg
                  << binaryNav.vehiclePosition.get().longitude_deg
                  << binaryNav.vehiclePosition.get().altitude_ref
                  << binaryNav.vehiclePosition.get().altitude_m;
        return true;
    }
};
} // namespace Serializer
} // namespace StdBinDecoder
