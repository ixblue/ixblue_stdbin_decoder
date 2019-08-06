#pragma once
#include <inttypes.h>

namespace StdBinDecoder
{
namespace Data
{

struct Dmi
{
    int32_t validityTime_100us; /* Time tag in steps of 100micros */
    int32_t pulse_count;        /* Number of pulses received since last DMI event */
};
} // namespace Data
} // namespace StdBinDecoder