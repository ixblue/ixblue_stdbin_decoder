#pragma once

#include "iXblue_stdbin_decoder/data_models/navigation_data/current_geographic_frame.h"
#include "iXblue_stdbin_decoder/data_serializer.h"

namespace StdBinDecoder
{
namespace Serializer
{
class CurrentGeographicFrame : public DataSerializer
{
public:
    CurrentGeographicFrame() : DataSerializer(11, 8) { }
    bool serialize(boost::asio::mutable_buffer& outBuffer,
                   const Data::BinaryNav& binaryNav) override
    {
        if (!binaryNav.currentGeographicFrame.is_initialized()) {
            return false;
        }
        outBuffer << binaryNav.currentGeographicFrame.get().north_msec
                  << binaryNav.currentGeographicFrame.get().east_msec;
        return true;
    }
};
} // namespace Serializer
} // namespace StdBinDecoder
