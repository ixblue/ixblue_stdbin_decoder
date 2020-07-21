#pragma once

#include "iXblue_stdbin_decoder/data_models/navigation_data/acceleration_geographic_frame.h"
#include "iXblue_stdbin_decoder/data_serializer.h"

namespace StdBinDecoder
{
namespace Serializer
{
class AccelerationGeographicFrame : public DataSerializer
{
public:
    AccelerationGeographicFrame() : DataSerializer(23, 12) { }
    bool serialize(boost::asio::mutable_buffer& outBuffer,
                   const Data::BinaryNav& binaryNav) override
    {
        if (!binaryNav.accelerationGeographicFrame.is_initialized()) {
            return false;
        }
        outBuffer << binaryNav.accelerationGeographicFrame.get().north_msec2
                  << binaryNav.accelerationGeographicFrame.get().east_msec2
                  << binaryNav.accelerationGeographicFrame.get().up_msec2;
        return true;
    }
};
} // namespace Serializer
} // namespace StdBinDecoder
