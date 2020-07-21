#pragma once

#include "iXblue_stdbin_decoder/data_models/navigation_data/current_geographic_frame_deviation.h"
#include "iXblue_stdbin_decoder/data_serializer.h"

namespace StdBinDecoder
{
namespace Serializer
{
class CurrentGeographicFrameDeviation : public DataSerializer
{
public:
    CurrentGeographicFrameDeviation() : DataSerializer(12, 8) { }
    bool serialize(boost::asio::mutable_buffer& outBuffer,
                   const Data::BinaryNav& binaryNav) override
    {
        if (!binaryNav.currentGeographicFrameDeviation.is_initialized()) {
            return false;
        }
        outBuffer << binaryNav.currentGeographicFrameDeviation.get().north_stddev_msec
                  << binaryNav.currentGeographicFrameDeviation.get().east_stddev_msec;
        return true;
    }
};
} // namespace Serializer
} // namespace StdBinDecoder
