#pragma once

#include "iXblue_stdbin_decoder/data_models/external_data/dvl_ground_speed.h"
#include "iXblue_stdbin_decoder/data_serializer.h"

namespace StdBinDecoder
{
namespace Serializer
{
class DvlGroundSpeed : public DataSerializer
{
public:
    DvlGroundSpeed(int bit_pose) : DataSerializer(bit_pose, 37) { }
    bool serialize(boost::asio::mutable_buffer& outBuffer,
                   const Data::BinaryNav& binaryNav) override
    {
        if (!getData(binaryNav).is_initialized()) {
            return false;
        }
        outBuffer << getData(binaryNav)->validityTime_100us
                  << getData(binaryNav)->dvl_id
                  << getData(binaryNav)->xv1_groundspeed_ms
                  << getData(binaryNav)->xv2_groundspeed_ms
                  << getData(binaryNav)->xv3_groundspeed_ms
                  << getData(binaryNav)->dvl_speedofsound_ms
                  << getData(binaryNav)->dvl_altitude_m
                  << getData(binaryNav)->xv1_stddev_ms
                  << getData(binaryNav)->xv2_stddev_ms
                  << getData(binaryNav)->xv3_stddev_ms;
        return true;
    }
    virtual const boost::optional<Data::DvlGroundSpeed>& getData(const Data::BinaryNav& binaryNav) const = 0;
};

class DvlGroundSpeed1 : public DvlGroundSpeed
{
public:
    DvlGroundSpeed1() : DvlGroundSpeed(10) { }

protected:
    const boost::optional<Data::DvlGroundSpeed>& getData(const Data::BinaryNav& binaryNav) const
    {
        return binaryNav.dvlGroundSpeed1;
    }
};

class DvlGroundSpeed2 : public DvlGroundSpeed
{
public:
    DvlGroundSpeed2() : DvlGroundSpeed(21) { }

protected:
    const boost::optional<Data::DvlGroundSpeed>& getData(const Data::BinaryNav& binaryNav) const
    {
        return binaryNav.dvlGroundSpeed2;
    }
};

} // namespace Serializer
} // namespace StdBinDecoder
