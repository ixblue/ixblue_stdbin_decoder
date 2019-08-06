#pragma once

namespace StdBinDecoder
{
namespace Data
{

/*! Raw Rotation Rate not compensated from earth rotation */
struct RawRotationRateVesselFrame
{
    float xv1_degsec;
    float xv2_degsec;
    float xv3_degsec;
};
} // namespace Data
} // namespace StdBinDecoder