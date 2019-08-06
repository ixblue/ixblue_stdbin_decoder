#pragma once
namespace StdBinDecoder
{
namespace Data
{

struct AttitudeQuaternion
{
    float q0; /*! Define as the scalar part of the quaternion */
    float q1;
    float q2;
    float q3;
};
} // namespace Data
} // namespace StdBinDecoder