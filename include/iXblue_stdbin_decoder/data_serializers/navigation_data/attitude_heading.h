#pragma once

#include "iXblue_stdbin_decoder/data_models/navigation_data/attitude_heading.h"
#include "iXblue_stdbin_decoder/data_serializer.h"

namespace StdBinDecoder
{
namespace Serializer
{
class AttitudeHeading : public DataSerializer
{
public:
    AttitudeHeading() : DataSerializer(0, 12) { }
    bool serialize(boost::asio::mutable_buffer& outBuffer,
                   const Data::BinaryNav& binaryNav) override
    {
        if (!binaryNav.attitudeHeading.is_initialized()) {
            return false;
        }
        outBuffer << binaryNav.attitudeHeading.get().heading_deg
                  << binaryNav.attitudeHeading.get().roll_deg
                  << binaryNav.attitudeHeading.get().pitch_deg;
        return true;
    }
};
} // namespace Serializer
} // namespace StdBinDecoder
