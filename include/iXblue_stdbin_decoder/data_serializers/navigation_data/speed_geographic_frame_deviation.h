#pragma once

#include "iXblue_stdbin_decoder/data_models/navigation_data/speed_geographic_frame_deviation.h"
#include "iXblue_stdbin_decoder/data_serializer.h"

namespace StdBinDecoder
{
namespace Serializer
{
class SpeedGeographicFrameDeviation : public DataSerializer
{
public:
    SpeedGeographicFrameDeviation() : DataSerializer(10, 12) { }
    bool serialize(boost::asio::mutable_buffer& outBuffer,
                   const Data::BinaryNav& binaryNav) override
    {
        if (!binaryNav.speedGeographicFrameDeviation.is_initialized()) {
            return false;
        }
        outBuffer << binaryNav.speedGeographicFrameDeviation.get().north_stddev_msec
                  << binaryNav.speedGeographicFrameDeviation.get().east_stddev_msec
                  << binaryNav.speedGeographicFrameDeviation.get().up_stddev_msec;
        return true;
    }
};
} // namespace Serializer
} // namespace StdBinDecoder
