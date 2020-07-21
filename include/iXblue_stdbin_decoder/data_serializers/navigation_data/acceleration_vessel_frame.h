#pragma once

#include "iXblue_stdbin_decoder/data_models/navigation_data/acceleration_vessel_frame.h"
#include "iXblue_stdbin_decoder/data_serializer.h"

namespace StdBinDecoder
{
namespace Serializer
{
class AccelerationVesselFrame : public DataSerializer
{
public:
    AccelerationVesselFrame() : DataSerializer(6, 12) { }
    bool serialize(boost::asio::mutable_buffer& outBuffer,
                   const Data::BinaryNav& binaryNav) override
    {
        if (!binaryNav.accelerationVesselFrame.is_initialized()) {
            return false;
        }
        outBuffer << binaryNav.accelerationVesselFrame.get().xv1_msec2
                  << binaryNav.accelerationVesselFrame.get().xv2_msec2
                  << binaryNav.accelerationVesselFrame.get().xv3_msec2;
        return true;
    }
};
} // namespace Serializer
} // namespace StdBinDecoder
