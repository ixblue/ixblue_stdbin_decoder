#pragma once

#include "iXblue_stdbin_decoder/data_models/extended_navigation_data/rotation_acceleration_vessel_frame.h"
#include "iXblue_stdbin_decoder/data_serializer.h"

namespace StdBinDecoder
{
namespace Serializer
{
class RotationAccelerationVesselFrame : public DataSerializer
{
public:
    RotationAccelerationVesselFrame() : DataSerializer(0, 12) { }
    bool serialize(boost::asio::mutable_buffer& outBuffer,
                   const Data::BinaryNav& binaryNav) override
    {
        if (!binaryNav.rotationAccelerationVesselFrame.is_initialized()) {
            return false;
        }
        outBuffer << binaryNav.rotationAccelerationVesselFrame.get().xv1_degsec2
                  << binaryNav.rotationAccelerationVesselFrame.get().xv2_degsec2
                  << binaryNav.rotationAccelerationVesselFrame.get().xv3_degsec2;
        return true;
    }
};
} // namespace Serializer
} // namespace StdBinDecoder
