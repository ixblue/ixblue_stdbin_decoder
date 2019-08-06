#pragma once
#include <inttypes.h>

namespace StdBinDecoder
{
namespace Data
{
struct SmartHeave
{
    uint32_t validityTime_100us;
    float smartHeave_m;
};
} // namespace Data
} // namespace StdBinDecoder
