#pragma once

#include "iXblue_stdbin_decoder/data_models/navigation_data/attitude_quaternion.h"
#include "iXblue_stdbin_decoder/data_serializer.h"

namespace StdBinDecoder
{
namespace Serializer
{
class AttitudeQuaternion : public DataSerializer
{
public:
    AttitudeQuaternion() : DataSerializer(26, 16) { }
    bool serialize(boost::asio::mutable_buffer& outBuffer,
                   const Data::BinaryNav& binaryNav) override
    {
        if (!binaryNav.attitudeQuaternion.is_initialized()) {
            return false;
        }
        outBuffer << binaryNav.attitudeQuaternion.get().q0
                  << binaryNav.attitudeQuaternion.get().q1
                  << binaryNav.attitudeQuaternion.get().q2
                  << binaryNav.attitudeQuaternion.get().q3;
        return true;
    }
};
} // namespace Serializer
} // namespace StdBinDecoder
