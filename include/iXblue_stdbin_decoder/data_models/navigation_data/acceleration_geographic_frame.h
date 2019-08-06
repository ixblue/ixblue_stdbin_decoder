#pragma once

namespace StdBinDecoder
{
namespace Data
{
/*! Acceleration in geographic frame not compensated from gravity at primary level arm */
struct AccelerationGeographicFrame
{
    float north_msec2; /*! m/s2 - Positive north */
    float east_msec2;  /*! m/s2 - Positive east */
    float up_msec2;    /*! m/s2 - Positive up */
};
} // namespace Data
} // namespace StdBinDecoder