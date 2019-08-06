#pragma once
namespace StdBinDecoder
{
namespace Data
{
struct HeadingRollPitchRate
{
    float heading_rate; /*! Deg/s - Positive when heading increase */
    float roll_rate;    /*! Deg/s - Positive when port going up */
    float pitch_rate;   /*! Deg/s - Positive when bow going down */
};
} // namespace Data
} // namespace StdBinDecoder
