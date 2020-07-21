#pragma once

#include "iXblue_stdbin_decoder/data_models/navigation_data/raw_acceleration_vessel_frame.h"
#include "iXblue_stdbin_decoder/data_serializer.h"

namespace StdBinDecoder
{
namespace Serializer
{
class RawAccelerationVesselFrame : public DataSerializer
{
public:
    RawAccelerationVesselFrame() : DataSerializer(28, 12) { }
    bool serialize(boost::asio::mutable_buffer& outBuffer,
                   const Data::BinaryNav& binaryNav) override
    {
        if (!binaryNav.rawAccelerationVesselFrame.is_initialized()) {
            return false;
        }
        outBuffer << binaryNav.rawAccelerationVesselFrame.get().xv1_msec2
                  << binaryNav.rawAccelerationVesselFrame.get().xv2_msec2
                  << binaryNav.rawAccelerationVesselFrame.get().xv3_msec2;
        return true;
    }
};
} // namespace Serializer
} // namespace StdBinDecoder
