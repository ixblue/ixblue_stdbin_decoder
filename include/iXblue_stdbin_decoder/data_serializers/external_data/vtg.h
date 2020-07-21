#pragma once

#include "iXblue_stdbin_decoder/data_models/external_data/vtg.h"
#include "iXblue_stdbin_decoder/data_serializer.h"

namespace StdBinDecoder
{
namespace Serializer
{
class Vtg : public DataSerializer
{
public:
    Vtg(int bit_pose) : DataSerializer(bit_pose, 17) { }
    bool serialize(boost::asio::mutable_buffer& outBuffer,
                   const Data::BinaryNav& binaryNav) override
    {
        if (!getData(binaryNav).is_initialized()) {
            return false;
        }
        outBuffer << getData(binaryNav)->validityTime_100us
                  << getData(binaryNav)->vtg_id
                  << getData(binaryNav)->true_course_deg
                  << getData(binaryNav)->magnetic_course_deg
                  << getData(binaryNav)->speed_over_ground_ms;
        return true;
    }
    virtual const boost::optional<Data::Vtg>& getData(const Data::BinaryNav& binaryNav) const = 0;
};

class Vtg1 : public Vtg
{
public:
    Vtg1() : Vtg(25) { }

protected:
    const boost::optional<Data::Vtg>& getData(const Data::BinaryNav& binaryNav) const
    {
        return binaryNav.vtg1;
    }
};

class Vtg2 : public Vtg
{
public:
    Vtg2() : Vtg(26) { }

protected:
    const boost::optional<Data::Vtg>& getData(const Data::BinaryNav& binaryNav) const
    {
        return binaryNav.vtg2;
    }
};

} // namespace Serializer
} // namespace StdBinDecoder
