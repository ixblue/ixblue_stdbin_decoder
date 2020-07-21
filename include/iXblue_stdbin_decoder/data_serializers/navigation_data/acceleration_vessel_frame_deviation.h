#pragma once

#include "iXblue_stdbin_decoder/data_models/navigation_data/acceleration_vessel_frame_deviation.h"
#include "iXblue_stdbin_decoder/data_serializer.h"

namespace StdBinDecoder
{
namespace Serializer
{
class AccelerationVesselFrameDeviation : public DataSerializer
{
public:
    AccelerationVesselFrameDeviation() : DataSerializer(29, 12) { }
    bool serialize(boost::asio::mutable_buffer& outBuffer,
                   const Data::BinaryNav& binaryNav) override
    {
        if (!binaryNav.accelerationVesselFrameDeviation.is_initialized()) {
            return false;
        }
        outBuffer << binaryNav.accelerationVesselFrameDeviation.get().xv1_stddev_msec2
                  << binaryNav.accelerationVesselFrameDeviation.get().xv2_stddev_msec2
                  << binaryNav.accelerationVesselFrameDeviation.get().xv3_stddev_msec2;
        return true;
    }
};
} // namespace Serializer
} // namespace StdBinDecoder
