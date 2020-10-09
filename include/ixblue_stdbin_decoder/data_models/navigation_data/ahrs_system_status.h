#pragma once
#include <inttypes.h>

namespace ixblue_stdbin_decoder
{
namespace Data
{

struct AHRSSystemStatus
{
    uint32_t status1 = 0;
    uint32_t status2 = 0;
    uint32_t status3 = 0;
};
} // namespace Data
} // namespace ixblue_stdbin_decoder