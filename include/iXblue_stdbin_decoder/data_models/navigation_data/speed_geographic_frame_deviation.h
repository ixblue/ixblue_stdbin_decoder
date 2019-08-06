#pragma once
namespace StdBinDecoder
{
namespace Data
{

struct SpeedGeographicFrameDeviation
{
    float north_stddev_msec;
    float east_stddev_msec;
    float up_stddev_msec;
};
} // namespace Data
} // namespace StdBinDecoder