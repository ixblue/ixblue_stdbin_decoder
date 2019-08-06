#pragma once
#include <inttypes.h>

namespace StdBinDecoder
{
namespace Data
{

struct AHRSSystemStatus
{
    uint32_t status1;
    uint32_t status2;
    uint32_t status3;
};
} // namespace Data
} // namespace StdBinDecoder