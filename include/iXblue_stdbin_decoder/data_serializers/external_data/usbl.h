#pragma once

#include "iXblue_stdbin_decoder/data_models/external_data/usbl.h"
#include "iXblue_stdbin_decoder/data_serializer.h"

namespace StdBinDecoder
{
namespace Serializer
{
class Usbl : public DataSerializer
{
public:
    Usbl(int bit_pose) : DataSerializer(bit_pose, 49) { }
    bool serialize(boost::asio::mutable_buffer& outBuffer,
                   const Data::BinaryNav& binaryNav) override
    {
        if (!getData(binaryNav).is_initialized()) {
            return false;
        }
        outBuffer << getData(binaryNav)->validityTime_100us
                  << getData(binaryNav)->usbl_id
                  << getData(binaryNav)->beacon_id
                  << getData(binaryNav)->latitude_deg
                  << getData(binaryNav)->longitude_deg
                  << getData(binaryNav)->altitude_m
                  << getData(binaryNav)->north_stddev_m
                  << getData(binaryNav)->east_stddev_m
                  << getData(binaryNav)->lat_lon_cov_m2
                  << getData(binaryNav)->altitude_stddev_m;
        return true;
    }
    virtual const boost::optional<Data::Usbl>& getData(const Data::BinaryNav& binaryNav) const = 0;
};

class Usbl1 : public Usbl
{
public:
    Usbl1() : Usbl(6) { }

protected:
    const boost::optional<Data::Usbl>& getData(const Data::BinaryNav& binaryNav) const
    {
        return binaryNav.usbl1;
    }
};

class Usbl2 : public Usbl
{
public:
    Usbl2() : Usbl(7) { }

protected:
    const boost::optional<Data::Usbl>& getData(const Data::BinaryNav& binaryNav) const
    {
        return binaryNav.usbl2;
    }
};

class Usbl3 : public Usbl
{
public:
    Usbl3() : Usbl(8) { }

protected:
    const boost::optional<Data::Usbl>& getData(const Data::BinaryNav& binaryNav) const
    {
        return binaryNav.usbl3;
    }
};

} // namespace Serializer
} // namespace StdBinDecoder
