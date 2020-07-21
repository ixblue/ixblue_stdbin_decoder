#pragma once

#include "iXblue_stdbin_decoder/data_models/external_data/gnss.h"
#include "iXblue_stdbin_decoder/data_serializer.h"

namespace StdBinDecoder
{
namespace Serializer
{
class Gnss : public DataSerializer
{
public:
    Gnss(int bit_pose) : DataSerializer(bit_pose, 46) { }
    bool serialize(boost::asio::mutable_buffer& outBuffer,
                   const Data::BinaryNav& binaryNav) override
    {
        if (!getData(binaryNav).is_initialized()) {
            return false;
        }
        outBuffer << getData(binaryNav)->validityTime_100us
                  << getData(binaryNav)->gnss_id
                  << getData(binaryNav)->gnss_quality
                  << getData(binaryNav)->latitude_deg
                  << getData(binaryNav)->longitude_deg
                  << getData(binaryNav)->altitude_m
                  << getData(binaryNav)->latitude_stddev_m
                  << getData(binaryNav)->longitude_stddev_m
                  << getData(binaryNav)->altitude_stddev_m
                  << getData(binaryNav)->lat_lon_stddev_m2
                  << getData(binaryNav)->geoidal_separation_m;
        return true;
    }
    virtual const boost::optional<Data::Gnss>& getData(const Data::BinaryNav& binaryNav) const = 0;
};

class Gnss1 : public Gnss
{
public:
    Gnss1() : Gnss(1) { }

protected:
    const boost::optional<Data::Gnss>& getData(const Data::BinaryNav& binaryNav) const
    {
        return binaryNav.gnss1;
    }
};

class Gnss2 : public Gnss
{
public:
    Gnss2() : Gnss(2) { }

protected:
    const boost::optional<Data::Gnss>& getData(const Data::BinaryNav& binaryNav) const
    {
        return binaryNav.gnss2;
    }
};

class GnssManual : public Gnss
{
public:
    GnssManual() : Gnss(3) { }

protected:
    const boost::optional<Data::Gnss>& getData(const Data::BinaryNav& binaryNav) const
    {
        return binaryNav.gnssManual;
    }
};

} // namespace Serializer
} // namespace StdBinDecoder
