#pragma once
namespace StdBinDecoder
{
namespace Data
{

/*! Acceleration compensated from gravity */
struct AccelerationVesselFrame
{
    float xv1_msec2; /*! m/s2 - Positive forward */
    float xv2_msec2; /*! m/s2 - Positive toward port */
    float xv3_msec2; /*! m/s2 - Positive up */
};
} // namespace Data
} // namespace StdBinDecoder