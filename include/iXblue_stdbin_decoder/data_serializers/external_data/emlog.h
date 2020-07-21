#pragma once

#include "iXblue_stdbin_decoder/data_models/external_data/emlog.h"
#include "iXblue_stdbin_decoder/data_serializer.h"

namespace StdBinDecoder
{
namespace Serializer
{
class Emlog : public DataSerializer
{
public:
    Emlog(int bit_pos) : DataSerializer(bit_pos, 13) { }
    bool serialize(boost::asio::mutable_buffer& outBuffer,
                   const Data::BinaryNav& binaryNav) override
    {
        if (!getData(binaryNav).is_initialized()) {
            return false;
        }
        outBuffer << getData(binaryNav)->validityTime_100us
                  << getData(binaryNav)->emlog_id
                  << getData(binaryNav)->xv1_waterSpeed_ms
                  << getData(binaryNav)->xv1_speed_stddev_ms;
        return true;
    }
    virtual const boost::optional<Data::Emlog>& getData(const Data::BinaryNav& binaryNav) const = 0;
};

class Emlog1 : public Emlog
{
public:
    Emlog1() : Emlog(4) { }

private:
    const boost::optional<Data::Emlog>& getData(const Data::BinaryNav& binaryNav) const
    {
        return binaryNav.emlog1;
    }
};

class Emlog2 : public Emlog
{
public:
    Emlog2() : Emlog(5) { }

private:
    const boost::optional<Data::Emlog>& getData(const Data::BinaryNav& binaryNav) const
    {
        return binaryNav.emlog2;
    }
};

} // namespace Serializer
} // namespace StdBinDecoder
