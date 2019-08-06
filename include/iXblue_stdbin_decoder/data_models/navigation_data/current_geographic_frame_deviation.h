#pragma once
namespace StdBinDecoder
{
namespace Data
{

struct CurrentGeographicFrameDeviation
{
    float north_stddev_msec; /*! Positive north */
    float east_stddev_msec;  /*! Positive east */
};
} // namespace Data
} // namespace StdBinDecoder