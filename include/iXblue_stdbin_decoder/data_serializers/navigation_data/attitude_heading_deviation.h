#pragma once

#include "iXblue_stdbin_decoder/data_models/navigation_data/attitude_heading_deviation.h"
#include "iXblue_stdbin_decoder/data_serializer.h"

namespace StdBinDecoder
{
namespace Serializer
{
class AttitudeHeadingDeviation : public DataSerializer
{
public:
    AttitudeHeadingDeviation() : DataSerializer(1, 12) { }
    bool serialize(boost::asio::mutable_buffer& outBuffer,
                   const Data::BinaryNav& binaryNav) override
    {
        if (!binaryNav.attitudeHeadingDeviation.is_initialized()) {
            return false;
        }
        outBuffer << binaryNav.attitudeHeadingDeviation.get().heading_stdDev_deg
                  << binaryNav.attitudeHeadingDeviation.get().roll_stdDev_deg
                  << binaryNav.attitudeHeadingDeviation.get().pitch_stdDev_deg;
        return true;
    }
};
} // namespace Serializer
} // namespace StdBinDecoder
