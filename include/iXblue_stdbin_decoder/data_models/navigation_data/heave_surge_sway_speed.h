#pragma once
namespace StdBinDecoder
{
namespace Data
{
struct HeaveSurgeSwaySpeed
{
    float realtime_heave_speed; /*! meter/sec - positive up in horizontal vehicle frame */
    float surge_speed; /*! meter/sec - positive forward in horizontal vehicle frame */
    float sway_speed;  /*! meter/sec - positive port side in horizontal vehicle frame */
};
} // namespace Data
} // namespace StdBinDecoder