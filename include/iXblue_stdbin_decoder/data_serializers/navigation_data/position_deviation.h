#pragma once

#include "iXblue_stdbin_decoder/data_models/navigation_data/position_deviation.h"
#include "iXblue_stdbin_decoder/data_serializer.h"

namespace StdBinDecoder
{
namespace Serializer
{
class PositionDeviation : public DataSerializer
{
public:
    PositionDeviation() : DataSerializer(8, 16) { }
    bool serialize(boost::asio::mutable_buffer& outBuffer,
                   const Data::BinaryNav& binaryNav) override
    {
        if (!binaryNav.positionDeviation.is_initialized()) {
            return false;
        }
        outBuffer << binaryNav.positionDeviation.get().north_stddev_m
                  << binaryNav.positionDeviation.get().east_stddev_m
                  << binaryNav.positionDeviation.get().north_east_corr
                  << binaryNav.positionDeviation.get().altitude_stddev_m;
        return true;
    }
};
} // namespace Serializer
} // namespace StdBinDecoder
