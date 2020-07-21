#pragma once

#include "iXblue_stdbin_decoder/data_models/external_data/lbl.h"
#include "iXblue_stdbin_decoder/data_serializer.h"

namespace StdBinDecoder
{
namespace Serializer
{
class Lbl : public DataSerializer
{
public:
    Lbl(int bit_pose) : DataSerializer(bit_pose, 41) { }
    bool serialize(boost::asio::mutable_buffer& outBuffer,
                   const Data::BinaryNav& binaryNav) override
    {
        if (!getData(binaryNav).is_initialized()) {
            return false;
        }
        outBuffer << getData(binaryNav)->validityTime_100us
                  << getData(binaryNav)->rfu
                  << getData(binaryNav)->beacon_id
                  << getData(binaryNav)->beacon_latitude_deg
                  << getData(binaryNav)->beacon_longitude_deg
                  << getData(binaryNav)->beacon_altitude_m
                  << getData(binaryNav)->range_m
                  << getData(binaryNav)->range_stddev_m;
        return true;
    }
    virtual const boost::optional<Data::Lbl>& getData(const Data::BinaryNav& binaryNav) const = 0;
};

class Lbl1 : public Lbl
{
public:
    Lbl1() : Lbl(14) { }

protected:
    const boost::optional<Data::Lbl>& getData(const Data::BinaryNav& binaryNav) const
    {
        return binaryNav.lbl1;
    }
};

class Lbl2 : public Lbl
{
public:
    Lbl2() : Lbl(15) { }

protected:
    const boost::optional<Data::Lbl>& getData(const Data::BinaryNav& binaryNav) const
    {
        return binaryNav.lbl2;
    }
};

class Lbl3 : public Lbl
{
public:
    Lbl3() : Lbl(16) { }

protected:
    const boost::optional<Data::Lbl>& getData(const Data::BinaryNav& binaryNav) const
    {
        return binaryNav.lbl3;
    }
};

class Lbl4 : public Lbl
{
public:
    Lbl4() : Lbl(17) { }

protected:
    const boost::optional<Data::Lbl>& getData(const Data::BinaryNav& binaryNav) const
    {
        return binaryNav.lbl4;
    }
};

} // namespace Serializer
} // namespace StdBinDecoder
