#pragma once
namespace StdBinDecoder
{
namespace Data
{

struct PositionDeviation
{
    float north_stddev_m;
    float east_stddev_m;
    float north_east_corr;
    float altitude_stddev_m;
};
} // namespace Data
} // namespace StdBinDecoder