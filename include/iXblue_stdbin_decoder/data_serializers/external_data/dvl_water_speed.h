#pragma once

#include "iXblue_stdbin_decoder/data_models/external_data/dvl_water_speed.h"
#include "iXblue_stdbin_decoder/data_serializer.h"

namespace StdBinDecoder
{
namespace Serializer
{
class DvlWaterSpeed : public DataSerializer
{
public:
    DvlWaterSpeed(int bit_pose) : DataSerializer(bit_pose, 33) { }
    bool serialize(boost::asio::mutable_buffer& outBuffer,
                   const Data::BinaryNav& binaryNav) override
    {
        if (!getData(binaryNav).is_initialized()) {
            return false;
        }
        outBuffer << getData(binaryNav)->validityTime_100us
                  << getData(binaryNav)->dvl_id
                  << getData(binaryNav)->xv1_waterspeed_ms
                  << getData(binaryNav)->xv2_waterspeed_ms
                  << getData(binaryNav)->xv3_waterspeed_ms
                  << getData(binaryNav)->dvl_speedofsound_ms
                  << getData(binaryNav)->xv1_stddev_ms
                  << getData(binaryNav)->xv2_stddev_ms
                  << getData(binaryNav)->xv3_stddev_ms;
        return true;

    }
    virtual const boost::optional<Data::DvlWaterSpeed>& getData(const Data::BinaryNav& binaryNav) const = 0;
};

class DvlWaterSpeed1 : public DvlWaterSpeed
{
public:
    DvlWaterSpeed1() : DvlWaterSpeed(11) { }

protected:
    const boost::optional<Data::DvlWaterSpeed>& getData(const Data::BinaryNav& binaryNav) const
    {
        return binaryNav.dvlWaterSpeed1;
    }
};

class DvlWaterSpeed2 : public DvlWaterSpeed
{
public:
    DvlWaterSpeed2() : DvlWaterSpeed(22) { }

protected:
    const boost::optional<Data::DvlWaterSpeed>& getData(const Data::BinaryNav& binaryNav) const
    {
        return binaryNav.dvlWaterSpeed2;
    }
};

} // namespace Serializer
} // namespace StdBinDecoder
