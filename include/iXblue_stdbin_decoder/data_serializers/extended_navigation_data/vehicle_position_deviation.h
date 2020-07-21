#pragma once

#include "iXblue_stdbin_decoder/data_models/extended_navigation_data/vehicle_position_deviation.h"
#include "iXblue_stdbin_decoder/data_serializer.h"

namespace StdBinDecoder
{
namespace Serializer
{
class VehiclePositionDeviation : public DataSerializer
{
public:
    VehiclePositionDeviation() : DataSerializer(6, 16) { }
    bool serialize(boost::asio::mutable_buffer& outBuffer,
                   const Data::BinaryNav& binaryNav) override
    {
        if (!binaryNav.vehiclePositionDeviation.is_initialized()) {
            return false;
        }
        outBuffer << binaryNav.vehiclePositionDeviation.get().north_stddev_m
                  << binaryNav.vehiclePositionDeviation.get().east_stddev_m
                  << binaryNav.vehiclePositionDeviation.get().north_east_corr
                  << binaryNav.vehiclePositionDeviation.get().altitude_stddev_m;
        return true;
    }
};
} // namespace Serializer
} // namespace StdBinDecoder
