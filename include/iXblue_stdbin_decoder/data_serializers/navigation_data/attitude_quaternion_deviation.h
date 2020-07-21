#pragma once

#include "iXblue_stdbin_decoder/data_models/navigation_data/attitude_quaternion_deviation.h"
#include "iXblue_stdbin_decoder/data_serializer.h"

namespace StdBinDecoder
{
namespace Serializer
{
class AttitudeQuaternionDeviation : public DataSerializer
{
public:
    AttitudeQuaternionDeviation() : DataSerializer(27, 12) { }
    bool serialize(boost::asio::mutable_buffer& outBuffer,
                   const Data::BinaryNav& binaryNav) override
    {
        if (!binaryNav.attitudeQuaternionDeviation.is_initialized()) {
            return false;
        }
        outBuffer << binaryNav.attitudeQuaternionDeviation.get().quat_stddev_xi1
                  << binaryNav.attitudeQuaternionDeviation.get().quat_stddev_xi2
                  << binaryNav.attitudeQuaternionDeviation.get().quat_stddev_xi3;
        return true;
    }
};
} // namespace Serializer
} // namespace StdBinDecoder
