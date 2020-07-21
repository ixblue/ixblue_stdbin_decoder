#pragma once

#include "iXblue_stdbin_decoder/data_models/navigation_data/realtime_heave_surge_sway.h"
#include "iXblue_stdbin_decoder/data_serializer.h"

namespace StdBinDecoder
{
namespace Serializer
{
class RealTimeHeaveSurgeSway : public DataSerializer
{
public:
    RealTimeHeaveSurgeSway() : DataSerializer(2, 16) { }
    bool serialize(boost::asio::mutable_buffer& outBuffer,
                   const Data::BinaryNav& binaryNav) override
    {
        if (!binaryNav.rtHeaveSurgeSway.is_initialized()) {
            return false;
        }
        outBuffer << binaryNav.rtHeaveSurgeSway.get().rt_heave_withoutBdL
                  << binaryNav.rtHeaveSurgeSway.get().rt_heave_atBdL
                  << binaryNav.rtHeaveSurgeSway.get().rt_surge_atBdL
                  << binaryNav.rtHeaveSurgeSway.get().rt_sway_atBdL;
        return true;
    }
};
} // namespace Serializer
} // namespace StdBinDecoder
