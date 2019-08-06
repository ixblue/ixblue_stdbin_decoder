#pragma once

namespace StdBinDecoder
{
namespace Data
{

/*! Rotation Acceleration are derivated from rotation rate */
struct RotationAccelerationVesselFrame
{
    float xv1_degsec2;
    float xv2_degsec2;
    float xv3_degsec2;
};
} // namespace Data
} // namespace StdBinDecoder